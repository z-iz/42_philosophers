/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 16:46:24 by larosale          #+#    #+#             */
/*   Updated: 2020/12/11 21:06:24 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Helper function for the "philo_take_forks" function.
** Depending on the "flag" value (LOCK or UNLOCK) and the philosopher's
** current state, locks or unlocks the respective forks.
*/

static void	fork_locker(t_philos *phil, int flag)
{
	sem_wait(phil->state_lock);
	if (flag == LOCK && phil->state == THINKING)
	{
		sem_post(phil->state_lock);
		sem_wait(g_ok_to_take);
		sem_wait(g_forks);
		return ;
	}
	else if (flag == LOCK && phil->state == TAKEN_FORK)
	{
		sem_post(phil->state_lock);
		sem_wait(g_forks);
		return ;
	}
	if (flag == UNLOCK)
	{
		sem_post(phil->state_lock);
		sem_post(g_forks);
		sem_post(g_ok_to_take);
		sem_post(g_forks);
		return ;
	}
}

/*
** Function to model the philosopher thinking.
*/

void		philo_think(t_philos *phil)
{
	sem_wait(phil->state_lock);
	phil->state = THINKING;
	print_status(phil->num, phil->state, get_time(phil->params));
	sem_post(phil->state_lock);
}

/*
** Function to model the philosopher taking forks.
*/

void		philo_take_forks(t_philos *phil)
{
	fork_locker(phil, LOCK);
	sem_wait(phil->state_lock);
	phil->state = TAKEN_FORK;
	print_status(phil->num, phil->state, get_time(phil->params));
	sem_post(phil->state_lock);
	fork_locker(phil, LOCK);
	sem_wait(phil->state_lock);
	phil->state = TAKEN_FORKS;
	print_status(phil->num, phil->state, get_time(phil->params));
	sem_post(phil->state_lock);
}

/*
** Function to model the philosopher eating.
** Sleeping is done in small fractions to reduce error in timing.
*/

void		philo_eat(t_philos *phil)
{
	int time;

	sem_wait(phil->state_lock);
	phil->state = EATING;
	time = get_time(phil->params);
	print_status(phil->num, phil->state, time);
	phil->last_eat = time;
	phil->num_ate++;
	sem_post(phil->state_lock);
	while (get_time(phil->params) - time < phil->params->t_eat)
		usleep(100);
	fork_locker(phil, UNLOCK);
}

/*
** Function to model the philosopher sleeping.
** Sleeping is done in small fractions to reduce error in timing.
*/

void		philo_sleep(t_philos *phil)
{
	int time;

	sem_wait(phil->state_lock);
	phil->state = SLEEPING;
	time = get_time(phil->params);
	print_status(phil->num, phil->state, time);
	sem_post(phil->state_lock);
	while (get_time(phil->params) - time < phil->params->t_sleep)
		usleep(100);
}
