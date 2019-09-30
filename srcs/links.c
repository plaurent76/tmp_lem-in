/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:49 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 17:49:28 by plaurent         ###   ########.fr       */
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
	tmp->len = 0;
	tmp->next = NULL;
	return (tmp);
}

void		add_link(t_link **src, t_link *new)
{
	t_link *tmp;

	tmp = (*src);
	if (*src && src)
	{
		if ((*src)->adjacent
			&& !ft_strcmp((*src)->adjacent->name, new->adjacent->name))
			return (del_path(&new));
		while ((*src)->next)
		{
			if (!ft_strcmp((*src)->next->adjacent->name, new->adjacent->name)
				&& (*src)->next->adjacent)
			{
				(*src) = tmp;
				return (del_path(&new));
			}
			(*src) = (*src)->next;
		}
		(*src)->next = new;
		(*src) = tmp;
	}
	else
		(*src) = new;
}
