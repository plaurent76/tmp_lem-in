/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:32:46 by eviana            #+#    #+#             */
/*   Updated: 2019/08/22 14:15:49 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void init_links_matrix(t_env *env)
{
	t_parsed_link *l;

	if (!(env->links = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_rooms, 0)))
		return ;
	// printf("fpl before iteration: %p\n", &(env->first_parsed_link));
	l = env->first_parsed_link;
	// while (l && l->prev && l->prev->room)
	// 	l = l->prev;
	while (l && l->next && l->room1 && l->room2)
	{
		// printf("adding link between: %d-%d\n",l->room1->idx,l->room2->idx);
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
		l = l->next;
		// free(l->prev);
	}
	if (l && l->room1 && l->room2)
	{
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
		// free(l);
	}
	// printf("fpl after iteration: %p\n", &(env->first_parsed_link));
}

static void init_name_tab(t_env *env)
{
	int				i;
	t_parsed_room	*r;

	i = -1;
	r = env->first_parsed_room;
	(env->room_names = alloc_matrix_char(256, env->nb_rooms))
	? 0 : perr(env, "Error: alloc_matric_char failed");
	while (++i < env->nb_rooms)
	{
		env->room_names[i] = ft_memcpy(env->room_names[i], r->room->id, 256);
		r = r->next;
	}
	free_parsed_rooms(env);
}

static void get_flow_max(t_env *env)
{
    int     i;
    int     flow_end;
	int		**tmp_node_exploration;

	(tmp_node_exploration = alloc_matrix_int(2, env->nb_rooms, -1))
	? 0 : perr(env, "Error: alloc_matric_int failed");
    env->flow_start_max = 0;
    flow_end = 0;
    i = 0;
    while (i < (int)env->nb_rooms)
    {
        if (env->links[0][i] == 1 && i != 0)
		{
			tmp_node_exploration[env->flow_start_max][0] = i;
			tmp_node_exploration[env->flow_start_max][1] = 0;
            env->flow_start_max++;
		}
        if (env->links[1][i] == 1 && i != 1)
            flow_end++;
        i++;
    }
	env->flow_max = flow_end <= env->flow_start_max ? flow_end : env->flow_start_max;
	env->node_exploration = alloc_matrix_int(2, env->flow_start_max, -1);
	i = -1;
	while (++i < env->flow_start_max)
		ft_memcpy(env->node_exploration[i], tmp_node_exploration[i], sizeof(int) * 2);
	// memcp(env->node_exploration, tmp_node_exploration, sizeof(int) * 2 * env->flow_start_max);
	free_matrix((void *)tmp_node_exploration, env->nb_rooms);
}

void		prepare_env(t_env *env)
{
	int		diff;

	diff = 1;
	env->nb_rooms = env->lpri + 1;
	// alloc room_free to track room occupation
	(env->room_free = (char *)malloc(sizeof(char)*env->nb_rooms)) ?
	0 : perr(env, "Error: env->room_free malloc failed");
	ft_memset(env->room_free, (char)1, env->nb_rooms);
	init_links_matrix(env);
	init_name_tab(env);
	get_flow_max(env);
	while ((4096 * env->flow_start_max) / diff > 22000)
		diff++;
	// if (diff > 1)
	// 	ft_printf("on a diviser le nb de paths par node par : %d", diff);
	env->max_paths_per_node = 4096 / diff;
	env->nb_paths = (int)((env->max_paths_per_node * env->flow_start_max)
	/ diff);
	// env->max_paths_per_node = env->nb_rooms * 2;
	// env->nb_paths = (int)(4096 + env->nb_rooms / 2);
}