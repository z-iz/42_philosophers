/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:23:33 by larosale          #+#    #+#             */
/*   Updated: 2020/12/11 20:43:06 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Monitoring function for each philosopher thread.
** Checks if the time passed since last eat exceeds the limit. If yes,
** returns and sets the philosopher's state to DIED.
*/

void		*philo_monitor(void *ptr)
{
	t_philos	*phil;
	int			time;

	phil = (t_philos *)ptr;
	while (1)
	{
		sem_wait(phil->state_lock);
		time = get_time(phil->params);
		if (time - phil->last_eat > phil->params->t_die
			&& phil->state != EATING)
		{
			phil->state = DIED;
			sem_post(phil->state_lock);
			return (NULL);
		}
		sem_post(phil->state_lock);
		usleep(CHECK_PERIOD);
	}
	return (NULL);
}

/*
** Helper function for "monitor_threads" function.
** Checks the status of a philosopher and returns 1 if it is in the final
** state, otherwise 0.
*/

static int	check_status(t_philos *philos, t_params *params, int *max)
{
	int max_eat;

	max_eat = *max;
	if (philos->state == DIED)
	{
		print_status(philos->num, philos->state, get_time(params));
		return (1);
	}
	if (!params->num_eats)
		return (0);
	if (philos->num_ate >= params->num_eats)
	{
		max_eat++;
		if (max_eat == params->thr_num)
		{
			print_status(philos->num, ATE, get_time(params));
			return (1);
		}
	}
	*max = max_eat;
	return (0);
}

/*
** Monitoring function to check the philosophers' status for death
** and maximum eats approach.
** If the final state is reached, the function returns and the program exits.
*/

void		monitor_threads(t_philos *philos, t_params *params)
{
	int	i;
	int	max_eat;

	while (1)
	{
		i = -1;
		max_eat = 0;
		while (++i < params->thr_num)
		{
			sem_wait((philos + i)->state_lock);
			if (check_status(philos + i, params, &max_eat))
			{
				sem_post((philos + i)->state_lock);
				return ;
			}
			sem_post((philos + i)->state_lock);
		}
		usleep(1000);
	}
}
