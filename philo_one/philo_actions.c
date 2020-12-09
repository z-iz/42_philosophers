/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 16:46:24 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 13:09:25 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_locker(t_philos *phil, int flag)
{
	int	left_fork;
	int	right_fork;

	left_fork = phil->num - 1;
	right_fork = (phil->num == 1 ? phil->params->thr_num - 1 : phil->num - 2);
	pthread_mutex_lock(&(phil->state_lock));
	if (flag == LOCK && phil->state == THINKING)
	{
		pthread_mutex_unlock(&(phil->state_lock));
		phil->type == LEFTY ? pthread_mutex_lock(g_forks + left_fork) :
			pthread_mutex_lock(g_forks + right_fork);
	}
	else if (flag == LOCK
		&& (phil->state == TAKEN_LFORK || phil->state == TAKEN_RFORK))
	{
		pthread_mutex_unlock(&(phil->state_lock));
		phil->type == LEFTY ? pthread_mutex_lock(g_forks + right_fork) :
			pthread_mutex_lock(g_forks + left_fork);
	}
	if (flag == UNLOCK)
	{
		pthread_mutex_unlock(&(phil->state_lock));
		pthread_mutex_unlock(g_forks + left_fork);
		pthread_mutex_unlock(g_forks + right_fork);
	}
}

void		philo_think(t_philos *phil)
{
	pthread_mutex_lock(&(phil->state_lock));
	phil->state = THINKING;
	print_status(phil->num, phil->state, get_time(phil->params));
	pthread_mutex_unlock(&(phil->state_lock));
}

void		philo_take_forks(t_philos *phil)
{
	fork_locker(phil, LOCK);
	pthread_mutex_lock(&(phil->state_lock));
	phil->state = (phil->type == RIGHTY ? TAKEN_RFORK : TAKEN_LFORK);
	print_status(phil->num, phil->state, get_time(phil->params));
	pthread_mutex_unlock(&(phil->state_lock));
	fork_locker(phil, LOCK);
	pthread_mutex_lock(&(phil->state_lock));
	phil->state = TAKEN_FORKS;
	print_status(phil->num, phil->state, get_time(phil->params));
	pthread_mutex_unlock(&(phil->state_lock));
}

void		philo_eat(t_philos *phil)
{
	int time;

	pthread_mutex_lock(&(phil->state_lock));
	phil->state = EATING;
	time = get_time(phil->params);
	print_status(phil->num, phil->state, time);
	phil->last_eat = time;
	phil->num_ate++;
	pthread_mutex_unlock(&(phil->state_lock));
	while (get_time(phil->params) - time < phil->params->t_eat)
		usleep(100);
	fork_locker(phil, UNLOCK);
}

void		philo_sleep(t_philos *phil)
{
	int time;

	pthread_mutex_lock(&(phil->state_lock));
	phil->state = SLEEPING;
	time = get_time(phil->params);
	print_status(phil->num, phil->state, time);
	pthread_mutex_unlock(&(phil->state_lock));
	while (get_time(phil->params) - time < phil->params->t_sleep)
		usleep(100);
}
