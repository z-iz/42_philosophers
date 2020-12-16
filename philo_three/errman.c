/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errman.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:04:14 by larosale          #+#    #+#             */
/*   Updated: 2020/12/16 18:51:44 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Prints error message depending on the error number "errnum".
** Error codes are defined in enum in "philo.h" header.
*/

int		errman(int errnum)
{
	if (errnum == OK)
		return (0);
	ft_putstr_fd("error: ", 2);
	errnum == ERR_SYS ? ft_putstr_fd("a system call error occurred", 2) : 0;
	errnum == ERR_ARGNUM ? ft_putstr_fd("wrong number of arguments", 2) : 0;
	errnum == ERR_ARGPHL ?
		ft_putstr_fd("number of philosophers must be at least 2", 2) : 0;
	errnum == ERR_ARGPHH ?
		ft_putstr_fd("number of philosophers must not exceed ", 2) : 0;
	errnum == ERR_ARGPHH ? ft_putnbr_fd(MAX_PROCESSES, 2) : 0;
	errnum == ERR_ARGTIM ?
		ft_putstr_fd("time argument must be positive and at least ", 2) : 0;
	errnum == ERR_ARGTIM ? ft_putnbr_fd(MIN_TIME, 2) : 0;
	errnum == ERR_ARGEAT ?
		ft_putstr_fd("number of times to eat must be positive", 2) : 0;
	ft_putstr_fd("\n", 2);
	return (1);
}
