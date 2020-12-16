/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:23:33 by larosale          #+#    #+#             */
/*   Updated: 2020/12/16 13:35:50 by larosale         ###   ########.fr       */
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
			print_status(phil->num, DIED, time);
			sem_post(phil->state_lock);
			sem_post(g_finish);
			return (NULL);
		}
		sem_post(phil->state_lock);
		usleep(CHECK_PERIOD);
	}
	return (NULL);
}

void		*eat_monitor(void *ptr)
{
	int			i;
	int			count;
	t_philos	*phil;

	phil = (t_philos *)ptr;
	i = -1;
	count = 0;
	while (count < phil->params->num_eats)
	{
		while (++i < phil->params->proc_num)
			sem_wait((phil + i)->eat_lock);
		count++;
	}
	print_status(0, ATE, get_time(phil->params));
	sem_post(g_finish);
	return (NULL);
}

int			start_eat_monitor(t_philos *phil)
{
	pthread_t	thread;

	if (phil->params->num_eats)
	{
		if (pthread_create(&thread, NULL, eat_monitor, phil)
			|| pthread_detach(thread))
			return (1);
	}
	return (0);
}
