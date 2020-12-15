/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/15 13:42:21 by larosale         ###   ########.fr       */
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
		sem_unlink((phil + num)->sem_name);
		free((phil + num)->sem_name);
		(phil + num)->sem_name = NULL;
		num++;
	}
	free(phil->params);
	phil->params = NULL;
	free(phil);
	phil = NULL;
	return ;
}

/*
** Cleans up the program state:
** - frees the "t_philos" array;
** - frees the "params" structure;
** - destroys "g_forks", "g_ok_to_take" and "g_write_lock" semaphores.
*/

int			cleanup(t_philos *phil, t_params *params, int errnum)
{
	sem_unlink("forks");
	sem_unlink("write_lock");
	sem_unlink("ok_to_take");
	if (params && !phil)
		free(params);
	if (phil)
		clear_philos(phil);
	return (errman(errnum));
}
