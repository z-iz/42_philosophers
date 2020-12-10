/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:10:39 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 21:25:54 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		temp->num = num + 1;
		temp->state = THINKING;
		temp->params = params;
		if ((temp->state_lock = sem_open("state_lock", O_CREAT, 0666, 1)) == SEM_FAILED)
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
	return (0);
}
