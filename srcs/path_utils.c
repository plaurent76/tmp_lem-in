/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:21:23 by paullaurent       #+#    #+#             */
/*   Updated: 2019/09/29 18:19:11 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_paths		*new_path(t_env *env, t_link *path)
{
	t_paths		*new;

	if (!(new = (t_paths*)malloc(sizeof(t_paths))))
		perr(env, "Error: malloc paths failed");
	new->len = path->len;
	new->path = path;
	new->next = NULL;
	return (new);
}

void		del_path(t_link **path)
{
	if (!path || !(*path))
		return ;
	if ((*path)->next != NULL)
		del_path(&(*path)->next);
	if (path)
	{
		free(*path);
		*path = NULL;
	}
}

static void	add_link_to_path(t_env *env, t_graph **cur,
		t_link **tmp_p, t_link **path)
{
	t_graph	*tmp;

	(*cur)->link->adjacent->visited = 2;
	add_link(path, new_link(env, (*cur)->link->adjacent));
	tmp = (*cur)->link->adjacent;
	(*cur)->link = *tmp_p;
	*cur = tmp;
	(*path)->len++;
}

t_link		*extract_path(t_env *env, t_link *path, t_graph *cur,
		t_graph *tmp_g)
{
	t_link	*tmp_p;

	cur->visited = 2;
	add_link(&path, new_link(env, cur));
	while (cur != env->end)
	{
		tmp_p = cur->link;
		while (cur->link && (cur->link->flow != -1
					|| cur->link->adjacent->visited == 2))
			cur->link = cur->link->next;
		if (!cur->link)
		{
			cur->link = tmp_p;
			env->start = tmp_g;
			del_path(&path);
			return (NULL);
		}
		add_link_to_path(env, &cur, &tmp_p, &path);
	}
	env->start = tmp_g;
	return (path);
}
