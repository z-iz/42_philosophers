/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 03:19:00 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_forks(t_params *params)
{
	int num;

	num = 0;
	while (num < params->thr_num)
	{
		pthread_mutex_destroy(&g_forks[num]);
		num++;
	}
	free(g_forks);
	return ;
}

static void	clear_philos(t_philos *phil)
{
	int	num;

	num = 0;
	while (num < phil->params->thr_num)
	{
		pthread_mutex_destroy(&((phil + num)->state_lock));
		num++;
	}
	free(phil->params);
	free(phil);
	return ;
}

int			cleanup(t_philos *phil, t_params *params, int errnum)
{
	if (g_forks && params)
		clear_forks(params);
	pthread_mutex_destroy(&g_write_lock);
	if (params && !phil)
		free(params);
	if (phil)
		clear_philos(phil);
	return (errman(errnum));
}
