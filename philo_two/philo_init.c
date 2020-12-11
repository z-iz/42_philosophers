/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:10:39 by larosale          #+#    #+#             */
/*   Updated: 2020/12/11 20:35:06 by larosale         ###   ########.fr       */
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
** Creates an array of data structures for philosopher's threads and returns
** the pointer to its first element.
*/

t_philos	*create_philos(t_params *params)
{
	t_philos	*philos;
	t_philos	*temp;
	int			num;

	num = 0;
	if (!(philos = ft_calloc(params->thr_num, sizeof(t_philos))))
		return (cleanup(NULL, params, ERR_SYS) ? NULL : NULL);
	temp = philos;
	while (num < params->thr_num)
	{
		if (!(temp->sem_name = ft_calloc(100, 1)))
			return (cleanup(NULL, params, ERR_SYS) ? NULL : NULL);
		temp->num = num + 1;
		make_sem_name(temp->sem_name, "state_lock", temp->num);
		temp->state = THINKING;
		temp->params = params;
		sem_unlink(temp->sem_name);
		temp->state_lock = sem_open(temp->sem_name, O_CREAT | O_EXCL, 0666, 1);
		if (temp->state_lock == SEM_FAILED)
			return (cleanup(philos, NULL, ERR_SYS) ? NULL : NULL);
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
	sem_unlink("forks");
	sem_unlink("write_lock");
	sem_unlink("ok_to_take");
	g_forks = sem_open("forks", O_CREAT | O_EXCL, 0666, params->thr_num);
	g_write_lock = sem_open("write_lock", O_CREAT | O_EXCL, 0666, 1);
	g_ok_to_take =
		sem_open("ok_to_take", O_CREAT | O_EXCL, 0666, params->thr_num - 1);
	if (g_forks == SEM_FAILED || g_write_lock == SEM_FAILED
		|| g_ok_to_take == SEM_FAILED)
		return (cleanup(NULL, params, ERR_SYS));
	return (0);
}
