/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:32:56 by larosale          #+#    #+#             */
/*   Updated: 2020/12/02 01:41:02 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Calculates the length of string "str".
*/

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

/*
** Writes a single symbol to the file descriptor "fd".
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
** Writes the string "str" to the file descriptor "fd".
*/

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

/*
** Writes integer number "n" to the output with file descriptor "fd".
*/

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	abs_n;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	else if (n < 0)
	{
		abs_n = -n;
		ft_putchar_fd('-', fd);
		if (abs_n > 9)
			ft_putnbr_fd(abs_n / 10, fd);
		ft_putchar_fd(((abs_n % 10) + '0'), fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}
