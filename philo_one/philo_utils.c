/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:09:27 by larosale          #+#    #+#             */
/*   Updated: 2020/12/09 03:04:53 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Gets the current system time since epoch, converts it to milliseconds,
** and if no starting time is specified - fills to params->start_time.
** Else, returns the diff between current time and starting time.
*/

void	print_status(int num, t_states state, int time)
{
	static int	finish = 0;

	pthread_mutex_lock(&g_write_lock);
	if (!finish)
	{
		if (state != ATE)
		{
			ft_putnbr_fd(time, 1);
			ft_putstr_fd(" ", 1);
			ft_putnbr_fd(num, 1);
		}
		state == TAKEN_LFORK || state == TAKEN_RFORK || state == TAKEN_FORKS
			? ft_putstr_fd(" has taken a fork\n", 1) : 0;
		state == EATING ? ft_putstr_fd(" is eating\n", 1) : 0;
		state == SLEEPING ? ft_putstr_fd(" is sleeping\n", 1) : 0;
		state == THINKING ? ft_putstr_fd(" is thinking\n", 1) : 0;
		if (state == DIED || state == ATE)
		{
			state == DIED ? ft_putstr_fd(" died\n", 1)
				: ft_putstr_fd("Philosophers ate max number of times\n", 1);
			finish = 1;
		}
	}
	pthread_mutex_unlock(&g_write_lock);
}

int		get_time(t_params *params)
{
	struct timeval	tp;
	long			time;

	if (gettimeofday(&tp, NULL) < 0)
	{
		errman(ERR_SYS);
		return (-1);
	}
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	if (!params->start_time)
	{
		params->start_time = time;
		return (0);
	}
	time -= params->start_time;
	return (time);
}
