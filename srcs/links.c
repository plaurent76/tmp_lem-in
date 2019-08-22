/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:49 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 13:42:05 by eviana           ###   ########.fr       */
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
		L2 = parsed_link;
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

// void		put_parsed_link(t_env *env, t_parsed_link *l)
// {
// 	(l->room1 && &(l->room1->id[0])) ? sp_putstr(1, &(l->room1->id[0]), '-')
// 	: perr(env, "Error: no room name to print");
// 	(l->room2 && &(l->room2->id[0])) ? sp_putstr(1, &(l->room2->id[0]), '\n')
// 	: perr(env, "Error: no room name to print");
// }

void		put_parsed_links(t_env *env)
{
	t_parsed_link *parsed;

	parsed = L1;
	if (parsed->room1 && parsed->room2)
	{
		put_parsed_links(env, parsed);
		while (parsed->next)
		{
			parsed = parsed->next;
			// put_parsed_link(env, parsed);
			(parsed->room1 && &(parsed->room1->id[0]))
			? sp_putstr(1, &(parsed->room1->id[0]), '-')
			: perr(env, "Error: no room name to print");
			(parsed->room2 && &(parsed->room2->id[0]))
			? sp_putstr(1, &(parsed->room2->id[0]), '\n')
			: perr(env, "Error: no room name to print");
		}
	}
}

void		put_links(t_env *env)
{
	int i = -1;
	int j;
	char c;

	while (++i < env->nb_rooms && ft_printf(" %d\t| ", i))
	{
		j = -1;
		while (++j < env->nb_rooms && env->links[i][j] != -1)
		{
			c = (char)((env->links[i][j] == 1) ? 'X' : '-');
			(j == 0 ? ft_printf("%c", c) : ft_printf(" | %c", c));
		}
		ft_printf("\n");
	}
}
