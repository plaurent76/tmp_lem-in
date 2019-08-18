/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:05 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:26:08 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*new_path(t_env *env, int *path, int size)
{
	t_path		*p;

	(p = (t_path *)malloc(sizeof(t_path))) ? 0 : perr(env, "t_path malloc failed");
	(p->rooms = alloc_array_int(size, -1)) ? 0 : perr(env, "t_path malloc failed");
	if (path != NULL)
		memcp(p->rooms, path, (sizeof(int) * size));
	p->current = 0;
	p->size = size;
	return (p);
}

// t_path	*duplicate_path(t_env *env, t_path *path)
// {
// 	t_path *p;
// 	t_path *new;

// 	p = path;
// 	new = new_path(env);
// 	while (p && p->prev && p->prev->room)
// 		p = p->prev;
// 	while (p && p->next)
// 	{
// 		p = p->next;
// 		new = add_path(env, new, p->room);
// 	}
// 	return (new);
// }

void	del_ant_path(t_path *path)
{
	if (!path)
		return ;
	if (path->rooms)
		free(path->rooms);
	free (path);
	path = NULL;
}

void	put_ant_path(t_path *path)
{
	t_path	*p;
	int 	i;

	p = path;
	if (!path || !path->rooms)
		return ;
	i = -1;
	while (++i < p->size && p->rooms[i] != -1)
		if (i == (p->size - 1) || p->rooms[i + 1] == -1)
		{
			plong(1, p->rooms[i], '\n');
		}
		else
		{
			plong(1, p->rooms[i], ' ');
			pstr(1, ">>", ' ');
		}
}
