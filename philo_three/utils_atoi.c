/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:39:49 by larosale          #+#    #+#             */
/*   Updated: 2020/12/01 23:39:52 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Checks, whether the intermediate result can go out of 'long' bounds.
*/

static int	check_result(long result, int sign, char current)
{
	long	limbase;
	int		limnum;
	int		num;

	result *= sign;
	num = current - '0';
	if (sign > 0)
	{
		limbase = LONG_MAX / 10;
		limnum = LONG_MAX % 10;
		if (result > limbase || (result == limbase && num > limnum))
			return (1);
	}
	else if (sign < 0)
	{
		limbase = LONG_MIN / 10;
		limnum = LONG_MIN % 10;
		if (result < limbase || (result == limbase && num < limnum))
			return (-1);
	}
	return (0);
}

/*
** Converts input string to an integer.
** Skips non-printable characters, reads sign, checks 'long' overflow.
*/

int			ft_atoi(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (check_result(result, sign, *str) == 1)
			return ((int)LONG_MAX);
		else if (check_result(result, sign, *str) == -1)
			return ((int)LONG_MIN);
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
