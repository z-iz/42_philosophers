/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:23:33 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 13:08:40 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_monitor(void *ptr)
{
	t_philos	*phil;
	int			time;

	phil = (t_philos *)ptr;
	while (1)
	{
		pthread_mutex_lock(&(phil->state_lock));
		time = get_time(phil->params);
		if (time - phil->last_eat > phil->params->t_die
			&& phil->state != EATING)
		{
			phil->state = DIED;
			pthread_mutex_unlock(&(phil->state_lock));
			return (NULL);
		}
		pthread_mutex_unlock(&(phil->state_lock));
		usleep(CHECK_PERIOD);
	}
	return (NULL);
}

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
			pthread_mutex_lock(&((philos + i)->state_lock));
			if (check_status(philos + i, params, &max_eat))
			{
				pthread_mutex_unlock(&((philos + i)->state_lock));
				return ;
			}
			pthread_mutex_unlock(&((philos + i)->state_lock));
		}
		usleep(1000);
	}
}
