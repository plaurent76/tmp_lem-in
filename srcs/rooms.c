/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:33 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/18 14:10:06 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void	set_parsed(t_env *env, t_parsed_room *parsed)
// {
// 	if (R2)
// 	{
// 		parsed->prev = R2;
// 		R2->next = parsed;
// 		R2 = R2->next;
// 	}
// 	else
// 	{
// 		parsed->prev = NULL;
// 		R1 ? perr(env, "Error: no last room among parsed") : 0;
// 		R2 = parsed;
// 		R1 = parsed;
// 	}
// }

t_graph		*new_room(t_env *env, char *name, long x, long y)
{
	t_graph	*tmp;

	(tmp = (t_graph *)malloc(sizeof(t_graph))) ? 0
	: perr(env, "Error: could not allocate parsed_room");
	if (name)
	{
		if (!(tmp->name = ft_strdup(name)))
			perr(env, "Error: malloc name failed");
	}
	else
		tmp->name = NULL;
	x > 2147483647 ? perr(env, "Error: room.x does not fit in an integer")
	: (tmp->x = (int)x);
	y > 2147483647 ? perr(env, "Error: room.y does not fit in an integer")
	: (tmp->y = (int)y);
	tmp->ant = 0;
	tmp->link = NULL;
	tmp->parent = NULL;
	tmp->visited = 0;
	tmp->next = NULL;
	return (tmp);
	// set_parsed(env, parsed_room);
}

void		add_room(t_env *env, t_graph *new, int state)
{
	t_graph		*tmp;

	tmp = env->graph;
	if (state == 3)
	{
		env->end = new;
		env->end_found = 1;
	}
	else if (state == 2 && env->graph && new)
	{
		new->next = env->graph;
		env->graph = new;
		env->start = env->graph;
	}
	else if (env->graph && new)
	{
		while (env->graph->next)
			env->graph = env->graph->next;
		env->graph->next = new;
		env->graph = tmp;
	}
	else
	{
		env->graph = new;
		state == 2 ? (env->start = env->graph) : 0;
	}
}

t_graph		*str_to_room(t_env *env, const char *s)
{
	t_graph *tmp;
	t_graph	*res;

	tmp = env->graph;
	(env->graph && env->graph->name) ? 0 : perr(env, "Error: no room to link to");
	s ? 0 : perr(env, "Error: no room name to link to");
	if (!ft_strcmp(env->graph->name, s))
		return (env->graph);
	while (env->graph->next && env->graph->next->name)
	{
		env->graph = env->graph->next;
		if (!ft_strcmp(env->graph->name, s))
		{
			res = env->graph;
			env->graph = tmp;
			return (res);
		}
	}
	env->graph = tmp;
	perr(env, "Error: name could not relate to any room.name");
	return (NULL);
}

// void		put_parsed_room(t_env *env, t_room *r)
// {
// 	&(r->id[0]) ? sp_putstr(1, r->id, ' ')
// 	: perr(env, "Error: no room name to print");
// 	r->x >= 0 ? sp_putlong(1, r->x, ' ')
// 	: perr(env, "Error: no room x to print");
// 	r->y >= 0 ? sp_putlong(1, r->y, '\0')
// 	: perr(env, "Error: no room y to print");
// 	if (r == env->start)
// 		sp_putstr(1, " [START]", '\n');
// 	else if (r == env->end)
// 		sp_putstr(1, " [END]", '\n');
// 	else
// 		write(1, "\n", 1);
// }

// void		put_parsed_rooms(t_env *env)
// {
// 	t_parsed_room *parsed;

// 	parsed = R1;
// 	(parsed && parsed->room)
// 	? sp_putstr(1, "Rooms list:", '\n') : perr(env, "Error: no parsed rooms");
// 	while (parsed)
// 	{
// 		put_parsed_room(env, parsed->room);
// 		//IS_SET_V ? put_parsed_room_links(env, parsed->room) : 0;
// 		parsed = parsed->next;
// 	}
// }

// void		put_rooms(t_env *env)
// {
// 	int i;

// 	ft_printf("\n room_id | room_name\n---------------------\n");
// 	i = -1;
// 	while (++i < env->nb_rooms) {
// 		ft_printf(" %d\t | %s\n", i, env->room_names[i]);
// 	}
// 	ft_printf("\n");
// }
