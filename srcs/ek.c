/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:20:25 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 16:09:04 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reset_visited(t_graph *graph)
{
	t_graph *tmp;

	tmp = graph;
	while (graph && graph->name)
	{
		graph->visited = 0;
		graph = graph->next;
	}
	graph = tmp;
	graph->visited = 1;
}

static int	room_used(t_env *env, t_graph *current)
{
	int	i;

	i = -1;
	if (current == env->start)
		return (0);
	while (current->link)
	{
		if (current->link->flow != 0)
			return (1);
		current->link = current->link->next;
	}
	return (0);
}

static int	check_flow(t_env *env, t_graph *current,
			t_graph *links, t_link *first_link)
{
	t_graph	*parent;
	t_link	*tmp;

	tmp = current->link;
	parent = current->parent;
	current->link = link_search(current, links->name);
	if (current->link->flow == -1)
		return (0);
	if (current->link->flow == 0)
	{
		current->link = first_link;
		if (parent != NULL
				&& link_search(current, parent->name)->flow == 0
				&& room_used(env, current))
		{
			current->link = tmp;
			return (0);
		}
	}
	current->link = tmp;
	return (1);
}

static int	bfs(t_env *env)
{
	t_queue	*queue;
	t_graph	*current;
	t_link	*tmp;

	queue = NULL;
	reset_visited(env->graph);
	add_to_queue(env, &queue, &env->graph[0]);
	while (queue)
	{
		current = next_room_queue(&queue);
		tmp = current->link;
		while (current->link)
		{
			if (current->link->adjacent->visited == 0 &&
				check_flow(env, current, current->link->adjacent, tmp))
			{
				current->link->adjacent->visited = 1;
				add_to_queue(env, &queue, current->link->adjacent);
				current->link->adjacent->parent = current;
			}
			current->link = current->link->next;
		}
		current->link = tmp;
	}
	return (env->end->visited);
}

int			ed_karp(t_env *env)
{
	int		flow_max;
	t_graph	*v;
	t_graph	*u;

	flow_max = 0;
	while (bfs(env))
	{
		++flow_max;
		v = env->end;
		while (v != env->start)
		{
			u = v->parent;
			link_search(u, v->name)->flow -= 1;
			link_search(v, u->name)->flow += 1;
			v = v->parent;
		}
		extract_solut(env, flow_max);
		env->t_len = 0;
	}
	return (flow_max);
}
