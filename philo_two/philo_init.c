/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:10:39 by larosale          #+#    #+#             */
/*   Updated: 2020/12/10 18:08:52 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		num_size(int num)
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
	char		*sem_name;

	num = 0;
	if (!(philos = ft_calloc(params->thr_num, sizeof(t_philos))) ||
		!(sem_name = ft_calloc(100, 1)))
		return (cleanup(NULL, params, ERR_SYS) ? NULL : NULL);
	temp = philos;
	while (num < params->thr_num)
	{
		memset(sem_name, 0, 100);
		temp->num = num + 1;
		make_sem_name(sem_name, "state_lock", temp->num);
		temp->state = THINKING;
		temp->params = params;
		temp->sem_name = sem_name;
		if ((temp->state_lock = sem_open(sem_name, O_CREAT, 0666, 1)) == SEM_FAILED)
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
	if ((g_forks = sem_open("forks", O_CREAT, 0666, params->thr_num)) == SEM_FAILED)
		return (cleanup(NULL, params, ERR_SYS));
	if ((g_write_lock = sem_open("write_lock", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (cleanup(NULL, params, ERR_SYS));
	if ((g_forks_count = sem_open("forks_count", O_CREAT, 0666, 1)) == SEM_FAILED)
		return (cleanup(NULL, params, ERR_SYS));
	return (0);
}
