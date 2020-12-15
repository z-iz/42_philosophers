/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:19:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/15 15:43:29 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Cleans up the program state:
** - frees the "phil" array;
** - frees the "params" structure;
** - frees the "g_forks" array;
*/

int			cleanup(t_philos *phil, t_params *params, int errnum)
{
	if (g_forks)
	{
		free(g_forks);
		g_forks = NULL;
	}
	if (params)
	{
		free(params);
		params = NULL;
	}
	if (phil)
	{
		free(phil);
		phil = NULL;
	}
	return (errman(errnum));
}
