/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:08:44 by eviana            #+#    #+#             */
/*   Updated: 2019/09/29 18:11:15 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*alloc_array_int(int n, int val)
{
	int		*array;
	int		i;

	i = -1;
	if (!(array = (int*)malloc(sizeof(int) * n)))
		return (NULL);
	while (++i < n)
		array[i] = val;
	return (array);
}

void	print_array_int(int *array, int n)
{
	int i;

	i = -1;
	while (++i < n && array[i] != -1)
		(i == 0 ? ft_putnbr(array[i]) : ft_printf("\t| %d", array[i]));
	ft_printf("\n");
}
