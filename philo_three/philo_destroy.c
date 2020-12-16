/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/16 19:09:51 by larosale         ###   ########.fr       */
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
		kill((phil + i)->pid, SIGKILL);
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
	sem_unlink(SEM_FIN);
	sem_close(g_forks);
	sem_close(g_write_lock);
	sem_close(g_ok_to_take);
	sem_close(g_finish);
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
		sem_unlink((phil + num)->eat_name);
		free((phil + num)->eat_name);
		(phil + num)->eat_name = NULL;
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
** Closes open unused semaphores in child processes
*/

int			close_sems_child(t_philos *start, t_philos *phil)
{
	int	i;

	i = -1;
	while (++i < start->params->proc_num)
	{
		if ((start + i) != phil)
		{
			if (sem_close((start + i)->state_lock)
				|| sem_close((start + i)->eat_lock))
				return (1);
		}
	}
	return (0);
}

/*
** Cleans up the program state:
** - kills all running child processes;
** - unlinks and closes semaphores;
** - frees the "t_philos" array;
** - frees the "params" structure;
*/

int			cleanup(t_philos *phil, t_params *params, int errnum)
{
	if (phil)
		stop_processes(phil);
	close_sems();
	if (params && !phil)
		free(params);
	if (phil)
		clear_philos(phil);
	return (errman(errnum));
}
