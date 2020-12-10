/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/10 12:13:50 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Helper function for the "cleanup" function.
** Clears the philosophers array of structures.
*/

static void	clear_philos(t_philos *phil)
{
	int	num;

	num = 0;
	while (num < phil->params->thr_num)
	{
		sem_close((phil + num)->state_lock);
		num++;
	}
	free(phil->params);
	free(phil);
	return ;
}


/*
** Cleans up the program state:
** - frees the "t_philos" array;
** - frees the "params" structure;
** - destroys "g_forks" and "g_write_lock" semaphores.
*/

int			cleanup(t_philos *phil, t_params *params, int errnum)
{
	if (g_forks)
		sem_close(g_forks);
	if (g_write_lock)
		sem_close(g_write_lock);
	if (params && !phil)
		free(params);
	if (phil)
		clear_philos(phil);
	return (errman(errnum));
}
