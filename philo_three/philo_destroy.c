/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/15 20:02:47 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Stops all running processes.
*/

static void	stop_processes(t_philos *phil)
{
	int	i;

	i = -1;
	while (++i < phil->params->proc_num)
		kill(phil->pid, SIGKILL);
	return ;
}

/*
** Closes semaphores in the parent process.
*/

static void	close_sems(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_TAKE);
	sem_close(g_forks);
	sem_close(g_write_lock);
	sem_close(g_ok_to_take);
}

/*
** Helper function for the "cleanup" function.
** Clears the philosophers array of structures.
*/

static void	clear_philos(t_philos *phil)
{
	int	num;

	num = 0;
	while (num < phil->params->proc_num)
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
	close_sems();
	stop_processes(phil);	
	if (params && !phil)
		free(params);
	if (phil)
		clear_philos(phil);
	return (errman(errnum));
}
