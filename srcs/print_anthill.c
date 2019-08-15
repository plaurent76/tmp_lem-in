/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:09 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:26:10 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// void	put_fwinfo(t_env *env)
// {
// 	pstr(1, "Paths used:", ' ');
// 	plong(1, 1, '\n');
// 	pstr(1, "Shortest path length:", ' ');
// 	plong(1, path_len(env->fw), '\n');
// 	pstr(1, "Turns to move the whole colony:", ' ');
// 	plong(1, (path_len(env->fw) + env->nb_ants), '\n');
// }

// void	put_room_links(t_env *env, t_room *room)
// {
// 	t_link *l;

// 	l = room->link;
// 	(room && &(room->id[0])) ? 0 : put_error(env, "Error: No room to target");
// 	l ? 0 : put_error(env, "Error: Room has no link");
// 	while ((l && l->prev && l->prev->room))
// 		(l = l->prev);
// 	pstr(1, room->id, ' ');
// 	pstr(1, "links:", ' ');
// 	while (l)
// 	{
// 		if (l->next)
// 			&(l->room->id[0]) ? pstr(1, &(l->room->id[0]), ' ') : 0;
// 		else
// 			&(l->room->id[0]) ? pstr(1, &(l->room->id[0]), '\n') : 0;
// 		l = l->next;
// 	}
// }

void	free_room_links(t_env *env, t_room *room)
{
	t_link *l;

	l = room->link;
	room ? 0 : put_error(env, "Error: No room to target");
	l ? 0 : put_error(env, "Error: Room has no link");
	while ((l && l->prev && l->prev->room))
		(l = l->prev);
	while (l->next)
	{
		l = l->next;
		l->prev ? free(l->prev) : 0;
	}
	l ? free(l) : 0;
}
