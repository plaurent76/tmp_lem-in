/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:07 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:12:08 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_colony(t_env *env)
{
	int i;

	i = env->nb_ants;
	if (env->colony)
		while (--i >= 0)
			env->colony[i] ? del_ant(env, env->colony[i]) : 0;
	if (env->colony != NULL)
	{
		free(env->colony);
		env->colony = NULL;
	}
}

// static void		free_rooms(t_env *env)
// {
// 	t_parsed_room *parsed;

// 	parsed = env->first_parsed_room;
// 	while (parsed && parsed->next)
// 	{
// 		parsed = parsed->next;
// 		(parsed->prev && parsed->prev->room && parsed->prev->room->link)
// 		? free_room_links(env, parsed->prev->room) : 0;
// 		(parsed->prev && parsed->prev->room) ? free(parsed->prev->room) : 0;
// 		parsed->prev ? free(parsed->prev) : 0;
// 	}
// 	(parsed && parsed->room && parsed->room->link)
// 	? free_room_links(env, parsed->room) : 0;
// 	(parsed && parsed->room) ? free(parsed->room) : 0;
// 	parsed ? free(parsed) : 0;
// 	env->first_parsed_room = NULL;
// 	R1 = NULL;
// 	R2 = NULL;
// 	L1 = NULL;
// 	L2 = NULL;
// }

void			free_parsed_links(t_env *env)
{
	t_parsed_link *l;

	l = env->first_parsed_link;
	while (l && l->next && l->room1 && l->room2)
	{
		l = l->next;
		free(l->prev);
	}
	if (l && l->room1 && l->room2)
		free(l);
	L1 = NULL;
	L2 = NULL;
}

void			free_parsed_rooms(t_env *env)
{
	t_parsed_room *r;

	r = env->last_parsed_room;
	while (r && r->prev)
	{
		r = r->prev;
		(r->next && r->next->room && r->next->room->link)
		? free_room_links(env, r->next->room) : 0;
		(r->next && r->next->room) ? free(r->next->room) : 0;
		r->next ? free(r->next) : 0;
	}
	(r && r->room && r->room->link)
	? free_room_links(env, r->room) : 0;
	(r && r->room) ? free(r->room) : 0;
	r ? free(r) : 0;
	R1 = NULL;
	R2 = NULL;
}

void			init_env(t_env *env)
{
	env->best_combo = NULL;
	env->best_score = 0;
	env->best_flow = 1;
	env->flow_max = 0;
	env->flow_start_max = 0;
	env->node_exploration = NULL;
	env->start = NULL;
	env->end = NULL;
	env->nb_rooms = 0;
	env->room_free = NULL;
	env->room_names = NULL;
	env->nb_paths = 0;
	env->nb_valid = 0;
	env->nb_ants = 0;
	env->lpri = 1;
	env->colony = NULL;
	env->paths = NULL;
	env->links = NULL;
	env->first_line = NULL;
	env->fw = NULL;
	env->option = 0;
	env->block = NULL;
	R1 = NULL;
	R2 = NULL;
	L1 = NULL;
	L2 = NULL;
}

void			deinit_env(t_env *env)
{
	free_matrix((void *)env->links, env->nb_rooms);
	free_matrix((void *)env->node_exploration, env->flow_start_max);
	free_matrix((void *)env->paths, env->nb_valid);
	free_matrix((void *)env->room_names, env->nb_rooms);
	free(env->best_combo);
	free(env->room_free);
	free_colony(env);
	free_parsed_rooms(env);
	free_parsed_links(env);
	free_lines(env);
	del_ant_path(env->fw);
}
