/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:13:49 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:13:49 by plaurent         ###   ########.fr       */
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

void	free_matrix(void **mx, int depth)
{
	if (!(depth && mx && *mx))
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

	while (++i < y && printf(" %d\t| ", i))
		print_array_int(mx[i], x);
}

void 	print_matrix_char(char **mx, int x, int y)
{
	int i = -1;

	while (++i < y && printf(" %d\t| ", i))
		write(1, mx[i], x);
}
