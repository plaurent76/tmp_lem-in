/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 11:59:04 by paullaurent       #+#    #+#             */
/*   Updated: 2019/09/29 18:28:22 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph	*next_room_queue(t_queue **queue)
{
	t_graph		*res;
	t_queue		*tmp;

	res = (*queue)->graph;
	tmp = (*queue)->next;
	free(*queue);
	*queue = tmp;
	return (res);
}

t_queue	*new_queue(t_env *env, t_graph *graph)
{
	t_queue		*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		perr(env, "Error: malloc queue failed");
	if (graph)
		new->graph = graph;
	else
		new->graph = NULL;
	new->next = NULL;
	return (new);
}

void	add_to_queue(t_env *env, t_queue **queue, t_graph *graph)
{
	t_queue *tmp;

	tmp = *queue;
	if (!*queue)
		(*queue) = new_queue(env, graph);
	else
	{
		while ((*queue)->next)
			*queue = (*queue)->next;
		(*queue)->next = new_queue(env, graph);
		*queue = tmp;
	}
}
