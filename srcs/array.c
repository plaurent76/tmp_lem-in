/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:13:42 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:13:42 by plaurent         ###   ########.fr       */
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

char	*alloc_array_char(int n, char val)
{
	char	*array;

	if (!(array = (char*)malloc(sizeof(char) * n)))
		return (NULL);
	ft_memset(array, val, n);
	return (array);
}

void 	print_array_int(int *array, int n)
{
	int i = -1;

	while (++i < n && array[i] != -1)
		(i == 0 ? ft_printf(" %d", array[i]) : ft_printf("\t| %d", array[i]));
	ft_printf("\n");
}
