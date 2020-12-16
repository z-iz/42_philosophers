/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:10:39 by larosale          #+#    #+#             */
/*   Updated: 2020/12/16 13:35:43 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Helper function for the "make_sem_name" function.
** Calculates the number "num" length in digits.
*/

static int	num_size(int num)
{
	int i;

	i = 1;
	while (num / 10)
	{
		num /= 10;
		i++;
	}
	return (i);
}

/*
** Helper function for "create_philos" function.
** Makes semaphore name from "str", with number "num" appended to it and
** saves it to the buffer.
*/

static void	make_sem_name(char *buffer, char *str, int num)
{
	int		num_len;

	num_len = num_size(num);
	while (*str)
		*buffer++ = *str++;
	*buffer++ = '_';
	while (num_len)
	{
		num %= 10;
		*(buffer + num_len - 1) = num + '0';
		num_len--;
	}
}

/*
** Creates an array of data structures for philosopher's processes and returns
** the pointer to its first element.
*/

t_philos	*create_philos(t_params *params)
{
	t_philos	*philos;
	t_philos	*temp;
	int			num;

	num = 0;
	if (!(philos = ft_calloc(params->proc_num, sizeof(t_philos))))
		return (cleanup(NULL, params, ERR_SYS) ? NULL : NULL);
	temp = philos;
	while (num < params->proc_num)
	{
		if (!(temp->sem_name = ft_calloc(100, 1))
			|| !(temp->eat_name = ft_calloc(100, 1)))
			return (cleanup(NULL, params, ERR_SYS) ? NULL : NULL);
		temp->num = num + 1;
		make_sem_name(temp->sem_name, "state_lock", temp->num);
		make_sem_name(temp->eat_name, "eat_lock", temp->num);
		temp->state = THINKING;
		temp->params = params;
		num++;
		temp++;
	}
	return (philos);
}

/*
** Creates semaphores for forks and output writing lock
*/

int			create_sems(t_params *params)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_TAKE);
	sem_unlink(SEM_FIN);
	g_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0666, params->proc_num);
	g_write_lock = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0666, 1);
	g_ok_to_take =
		sem_open(SEM_TAKE, O_CREAT | O_EXCL, 0666, params->proc_num - 1);
	g_finish = sem_open(SEM_FIN, O_CREAT | O_EXCL, 0666, 0);
	if (g_forks == SEM_FAILED || g_write_lock == SEM_FAILED
		|| g_ok_to_take == SEM_FAILED || g_finish == SEM_FAILED)
		return (cleanup(NULL, params, ERR_SYS));
	return (0);
}

/*
** Opens semaphores in child processes
*/

int			open_sems_child(t_philos *phil)
{
	g_forks = sem_open(SEM_FORKS, 0);
	g_write_lock = sem_open(SEM_WRITE, 0);
	g_ok_to_take = sem_open(SEM_TAKE, 0);
	g_finish = sem_open(SEM_FIN, 0);
	sem_unlink(phil->sem_name);
	phil->state_lock = sem_open(phil->sem_name, O_CREAT | O_EXCL, 0666, 1);
	sem_unlink(phil->eat_name);
	phil->state_lock = sem_open(phil->eat_name, O_CREAT | O_EXCL, 0666, 0);
	if (g_forks == SEM_FAILED || g_write_lock == SEM_FAILED
		|| g_finish == SEM_FAILED || g_ok_to_take == SEM_FAILED
		|| phil->state_lock == SEM_FAILED || phil->eat_lock == SEM_FAILED)
		return (1);
	return (0);
}
