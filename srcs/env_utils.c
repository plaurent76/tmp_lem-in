/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:34 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:36 by pde-rent         ###   ########.fr       */
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

static void		free_rooms(t_env *env)
{
	t_parsed_room *parsed;

	parsed = env->first_parsed_room;
	while (parsed && parsed->next)
	{
		parsed = parsed->next;
		(parsed->prev && parsed->prev->room && parsed->prev->room->link)
		? free_room_links(env, parsed->prev->room) : 0;
		(parsed->prev && parsed->prev->room) ? free(parsed->prev->room) : 0;
		parsed->prev ? free(parsed->prev) : 0;
	}
	(parsed && parsed->room && parsed->room->link)
	? free_room_links(env, parsed->room) : 0;
	(parsed && parsed->room) ? free(parsed->room) : 0;
	parsed ? free(parsed) : 0;
	env->first_parsed_room = NULL;
	R1 = NULL;
	R2 = NULL;
	L1 = NULL;
	L2 = NULL;
}

static void		free_parsed_links(t_env *env)
{
	t_parsed_link *parsed;

	parsed = env->first_parsed_link;
	while (parsed && parsed->next)
	{
		parsed = parsed->next;
		parsed->prev ? free(parsed->prev) : 0;
	}
	if (parsed != NULL)
	{
		free(parsed);
		env->first_parsed_link = NULL;
		env->last_parsed_link = NULL;
	}
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
	R1 = NULL;
	R2 = NULL;
	L1 = NULL;
	L2 = NULL;
}

void			deinit_env(t_env *env)
{
	free_matrix_int(env->links, env->nb_rooms);
	free_matrix_int(env->node_exploration, env->flow_start_max);
	free_matrix_int(env->paths, env->nb_valid);
	free_colony(env);
	free_rooms(env);
	free_parsed_links(env);
	free_lines(env);
	del_ant_path(env->fw);
}
