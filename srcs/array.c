/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:39 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:40 by pde-rent         ###   ########.fr       */
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
	mems(array, val, n);
	return (array);
}

void 	print_array_int(int *array, int n)
{
	int i = -1;

	while (++i < n && array[i] != -1)
		(i == 0 ? printf(" %d", array[i]) : printf("\t| %d", array[i]));
	printf("\n");
}
