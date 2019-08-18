/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:44 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:45 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*add_link(t_room *new_room, t_link *prev_link)
{
	t_link *link;

	link = (t_link *)malloc(sizeof(t_link));
	link->room = new_room;
	link->prev = prev_link;
	link->next = NULL;
	return (link);
}

void		new_link(t_env *env, t_room *room1, t_room *room2)
{
	t_parsed_link *parsed_link;

	if (!room1 || !room2)
		perr(env, "Error: tried to link non-existing room");
	parsed_link = (t_parsed_link *)malloc(sizeof(t_parsed_link));
	parsed_link->room1 = room1;
	parsed_link->room2 = room2;
	parsed_link->next = NULL;
	if (L2)
	{
		parsed_link->prev = L2;
		L2->next = parsed_link;
		L2 = L2->next;
	}
	else
	{
		parsed_link->prev = NULL;
		L1 ? perr(env, "Error: no last link among parsed") : 0;
		L2 = parsed_link;
		L1 = parsed_link;
	}
	link_rooms(env, room1, room2);
}

void		link_rooms(t_env *env, t_room *room1, t_room *room2)
{
	room1 == room2 ? perr(env, "Error: room linked to itself") : 0;
	if (room1->link)
	{
		room1->link->next = add_link(room2, room1->link);
		room1->link = room1->link->next;
	}
	else
		room1->link = add_link(room2, NULL);
	if (room2->link)
	{
		room2->link->next = add_link(room1, room2->link);
		room2->link = room2->link->next;
	}
	else
		room2->link = add_link(room1, NULL);
}

void		put_link(t_env *env, t_parsed_link *l)
{
	(l->room1 && &(l->room1->id[0])) ? pstr(1, &(l->room1->id[0]), '-')
	: perr(env, "Error: no room name to print");
	(l->room2 && &(l->room2->id[0])) ? pstr(1, &(l->room2->id[0]), '\n')
	: perr(env, "Error: no room name to print");
}

void		put_links(t_env *env)
{
	t_parsed_link *parsed;

	parsed = L1;
	if (parsed->room1 && parsed->room2)
	{
		put_link(env, parsed);
		while (parsed->next)
		{
			parsed = parsed->next;
			put_link(env, parsed);
		}
	}
}
