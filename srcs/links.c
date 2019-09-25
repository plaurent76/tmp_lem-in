/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:49 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/25 10:47:32 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*link_search(t_graph *graph, char *name)
{
	t_link	*tmp;
	t_link	*res;

	if (!name || !graph || !graph->link)
		return (NULL);
	tmp = graph->link;
	while (graph->link && ft_strcmp(graph->link->adjacent->name, name))
		graph->link = graph->link->next;
	res = graph->link;
	graph->link = tmp;
	return (res);
}

t_link		*new_link(t_env *env, t_graph *room)
{
	t_link	*tmp;

	if (!(tmp = (t_link *)malloc(sizeof(t_link))))
		perr(env, "Error: failling malloc link");
	if (room)
		tmp->adjacent = room;
	else
		tmp->adjacent = NULL;
	tmp->flow = 0;
	tmp->next = NULL;
	return (tmp);
}

void		add_link(t_link **src, t_link *new)
{
	t_link *tmp;

	tmp = (*src);
	if (*src && src)
	{
		if ((*src)->adjacent && !ft_strcmp((*src)->adjacent->name, new->adjacent->name))
			return ;
		while((*src)->next)
		{
			if ((*src)->next->adjacent && !ft_strcmp((*src)->next->adjacent->name, new->adjacent->name))
			{
				(*src) = tmp;
				return ;
			}
			(*src) = (*src)->next;
		}
		(*src)->next = new;
		(*src) = tmp;
	}
	else
		(*src) = new;
}

// void		new_link(t_env *env, t_graph *room1, t_graph *room2)
// {
// 	if (!room1 || !room2)
// 		perr(env, "Error: tried to link non-existing room");
// 		add_link(&room1->link, new_link(room2));
// 		add_link(&room2->link, new_link(room1));
// }

// void		link_rooms(t_env *env, t_room *room1, t_room *room2)
// {
// 	room1 == room2 ? perr(env, "Error: room linked to itself") : 0;
// 	if (room1->link)
// 	{
// 		room1->link->next = add_link(room2, room1->link);
// 		room1->link = room1->link->next;
// 	}
// 	else
// 		room1->link = add_link(room2, NULL);
// 	if (room2->link)
// 	{
// 		room2->link->next = add_link(room1, room2->link);
// 		room2->link = room2->link->next;
// 	}
// 	else
// 		room2->link = add_link(room1, NULL);
// }

// void		put_parsed_link(t_env *env, t_parsed_link *l)
// {
// 	(l->room1 && &(l->room1->id[0])) ? sp_putstr(1, &(l->room1->id[0]), '-')
// 	: perr(env, "Error: no room name to print");
// 	(l->room2 && &(l->room2->id[0])) ? sp_putstr(1, &(l->room2->id[0]), '\n')
// 	: perr(env, "Error: no room name to print");
// }

// void		put_parsed_links(t_env *env)
// {
// 	t_parsed_link *parsed;

// 	parsed = L1;
// 	if (parsed->room1 && parsed->room2)
// 	{
// 		// put_parsed_link(env, parsed);
// 		(parsed->room1 && &(parsed->room1->id[0]))
// 			? sp_putstr(1, &(parsed->room1->id[0]), '-')
// 			: perr(env, "Error: no room name to print");
// 			(parsed->room2 && &(parsed->room2->id[0]))
// 			? sp_putstr(1, &(parsed->room2->id[0]), '\n')
// 			: perr(env, "Error: no room name to print");
// 		while (parsed->next)
// 		{
// 			parsed = parsed->next;
// 			// put_parsed_link(env, parsed);
// 			(parsed->room1 && &(parsed->room1->id[0]))
// 			? sp_putstr(1, &(parsed->room1->id[0]), '-')
// 			: perr(env, "Error: no room name to print");
// 			(parsed->room2 && &(parsed->room2->id[0]))
// 			? sp_putstr(1, &(parsed->room2->id[0]), '\n')
// 			: perr(env, "Error: no room name to print");
// 		}
// 	}
// }

// void		put_links(t_env *env)
// {
// 	int i = -1;
// 	int j;
// 	char c;

// 	while (++i < env->nb_rooms && ft_printf(" %d\t| ", i))
// 	{
// 		j = -1;
// 		while (++j < env->nb_rooms && env->links[i][j] != -1)
// 		{
// 			c = (char)((env->links[i][j] == 1) ? 'X' : '-');
// 			(j == 0 ? ft_printf("%c", c) : ft_printf(" | %c", c));
// 		}
// 		ft_printf("\n");
// 	}
// }
