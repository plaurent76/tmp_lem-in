/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:31 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:33 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// int		in_path(t_path *path, t_room *r)
// {
// 	t_path *p;

// 	p = path;
// 	if (r && p && p->room)
// 	{
// 		while (p && p->prev)
// 			p = p->prev;
// 		while (p)
// 		{
// 			if (p->room == r)
// 				return (1);
// 			else
// 				p = p->next;
// 		}
// 		return (0);
// 	}
// 	return (-1);
// }

int		path_len(int *path)
{
	int		i;

	i = 0;
	while (path[i] != -1)
		i++;
	return (i);
}

int		count_rooms(t_room *r)
{
	t_link	*l;
	int		cnt;

	cnt = 1;
	if (!(r && r->link && r->link->room))
		return (0);
	l = r->link;
	while (l && l->prev && l->prev->room)
		l = l->prev;
	while (l->next && l->next->room)
	{
		l = l->next;
		++cnt;
	}
	return (cnt);
}
