/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:09:10 by larosale          #+#    #+#             */
/*   Updated: 2020/12/02 13:09:34 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Allocates memory for "count" objects, each of size "size" and fills with 0's.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	mem = malloc(count * size);
	if (mem)
		memset(mem, 0, count * size);
	return (mem);
}
