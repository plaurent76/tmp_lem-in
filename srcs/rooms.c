/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:33 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/29 12:59:41 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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