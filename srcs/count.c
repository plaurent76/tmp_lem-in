/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:14:01 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:14:02 by plaurent         ###   ########.fr       */
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

int		path_len(int *path, int size)
{
	int		i;

	i = 0;
	while (path[i] != -1 && i < size)
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
