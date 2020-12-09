/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:10:39 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 15:14:01 by larosale         ###   ########.fr       */
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
		if (temp->num % 2)
			temp->type = RIGHTY;
		temp->params = params;
		if (pthread_mutex_init(&(temp->state_lock), NULL))
			return (cleanup(philos, NULL, ERR_SYS) ? NULL : NULL);
		num++;
		temp++;
	}
	return (philos);
}

/*
** Creates an array of mutexes used to lock resources (forks).
** Pointer to the created array is saved in the global variable "g_forks".
*/

int			create_forks(t_params *params)
{
	pthread_mutex_t *temp;
	int				num;

	num = 0;
	if (!(g_forks = ft_calloc(params->thr_num, sizeof(pthread_mutex_t))))
		return (cleanup(NULL, params, ERR_SYS));
	temp = g_forks;
	while (num < params->thr_num)
	{
		if (pthread_mutex_init(temp, NULL))
			return (cleanup(NULL, params, ERR_SYS));
		num++;
		temp++;
	}
	return (0);
}
