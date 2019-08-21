/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:09 by pde-rent          #+#    #+#             */
/*   Updated: 2019/08/21 16:29:52 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// void	put_fwinfo(t_env *env)
// {
// 	// sp_putstr(1, "Paths used:", ' ');
// 	// sp_putlong(1, 1, '\n');
// 	// sp_putstr(1, "Shortest path length:", ' ');
// 	// sp_putlong(1, path_len(env->fw), '\n');
// 	// sp_putstr(1, "Turns to move the whole colony:", ' ');
// 	// sp_putlong(1, (path_len(env->fw) + env->nb_ants), '\n');
// }

void	put_parsed_room_links(t_env *env, t_room *room)
{
	t_link *l;

	l = room->link;
	(room && &(room->id[0])) ? 0 : perr(env, "Error: No room to target");
	l ? 0 : perr(env, "Error: Room has no link");
	while ((l && l->prev && l->prev->room))
		(l = l->prev);
	sp_putstr(1, room->id, ' ');
	sp_putstr(1, "links:", ' ');
	while (l)
	{
		if (l->next)
			&(l->room->id[0]) ? sp_putstr(1, &(l->room->id[0]), ' ') : 0;
		else
			&(l->room->id[0]) ? sp_putstr(1, &(l->room->id[0]), '\n') : 0;
		l = l->next;
	}
}

void	free_room_links(t_env *env, t_room *room)
{
	t_link *l;

	l = room->link;
	room ? 0 : perr(env, "Error: No room to target");
	l ? 0 : perr(env, "Error: Room has no link");
	while ((l && l->prev && l->prev->room))
		(l = l->prev);
	while (l->next)
	{
		l = l->next;
		l->prev ? free(l->prev) : 0;
	}
	l ? free(l) : 0;
}
