/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:39 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:40 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		**alloc_matrix_int(int x, int y, int val)
{
	int		i;
	int		**mx;
	
	i = -1;
	if (!(mx = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	while (++i < y)
		if (!(mx[i] = alloc_array_int(x, val)))
			return (NULL);
	return (mx);
}

char	**alloc_matrix_char(int x, int y)
{
	int		i;
	char	**mx;
	
	i = -1;
	if (!(mx = (char**)malloc(sizeof(char*) * y)))
		return (NULL);
	while (++i < y)
		if (!(mx[i] = alloc_array_char(x, (char)0)))
			return (NULL);
	return (mx);
}

void	free_matrix_int(int **mx, int depth)
{
	if (!(&mx && mx && *mx))
		return ;
	while (--depth >= 0)
		if (mx[depth] != NULL)
			free(mx[depth]);
	free(mx);
	mx = NULL;
}

void 	print_matrix_int(int **mx, int x, int y)
{
	int i = -1;

	while (++i < y)
	{
		printf("%d\t | ", i);
		print_array_int(mx[i], x);
	}
}
