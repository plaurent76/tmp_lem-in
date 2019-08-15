/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genetic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:39 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:40 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	*memcp(void *mem2, const void *mem1, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		((char*)mem2)[i] = ((char*)mem1)[i];
	return (mem2);
}

void	*mems(void *mem, int c, size_t n)
{
	size_t i;

	i = -1;
	while (++i < n)
		((char*)mem)[i] = (unsigned char)c;
	return (mem);
}
