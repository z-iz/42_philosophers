/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 17:23:33 by larosale          #+#    #+#             */
/*   Updated: 2020/12/15 20:01:16 by larosale         ###   ########.fr       */
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
			print_status(phil->num, phil->state, get_time(phil->params));
			exit(EXIT_DEAD);
		}
		if (phil->num_ate >= phil->params->num_eats)
			exit(EXIT_ATE);
		sem_post(phil->state_lock);
		usleep(CHECK_PERIOD);
	}
	return (NULL);
}
