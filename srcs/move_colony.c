/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_colony.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:55 by pde-rent          #+#    #+#             */
/*   Updated: 2019/08/21 14:36:26 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int *get_combo_paths_len(t_env *env)
{
	int i;
	int *paths_len;

	if (!(paths_len = alloc_array_int(env->best_flow, 0)))
		return (NULL);
	i = -1;
	while (++i < env->best_flow)
		paths_len[i] = path_len(env->paths[env->best_combo[i]], env->nb_rooms);
	return (paths_len);
}

int *get_ants_per_node(t_env *env)
{
	int *paths_len;
	int *ants_per_node;
	// int min_len;
	// int max_len;
	int diff;
	int i;
	int ants_left;

	(paths_len = get_combo_paths_len(env)) ? 0
	: perr(env, "Error: paths_len malloc failed");
	(ants_per_node = alloc_array_int(env->best_flow, 0)) ? 0
	: perr(env, "Error: ants_per_node malloc failed");

	// i = -1;
	// max_len = 0;
	// min_len = env->nb_rooms;
	// while (++i < env->best_flow)
	// 	paths_len[i] > max_len ? (max_len = paths_len[i])
	// 	: paths_len[i] < min_len ? (min_len = paths_len[i]) : 0;^

	// min_len = paths_len[0];
	// max_len = paths_len[env->best_flow - 1];
	ants_left = env->nb_ants; // % (min_len * env->best_flow);
	i = -1;
	while (++i < env->best_flow - 1)
	{
		diff = paths_len[i + 1] - paths_len[i];
		if (diff >= 0 && ((diff + paths_len[i] - 1) > ants_left)) // ici un -1 a ete rajouter
		{
			ants_per_node[i] += ants_left;
			ants_left = 0;
			break;
		}
		else if (diff >= 0 && diff < ants_left)
		{
			// ants_per_node[i] += paths_len[i];
			ants_per_node[i] += diff;
			ants_left -= diff;
		}
	}
	i = 0;
	while (--ants_left >= 0)
	{
		ants_per_node[i]++;
		i = (i == (env->best_flow - 1)) ? 0 : (i + 1);
	}
	if (IS_SET_V)
	{
		printf("env->best_combo: paths_len:\n");
		print_array_int(paths_len, env->best_flow);
		printf("env->best_combo: ants_per_node:\n");
		print_array_int(ants_per_node, env->best_flow);
	}
	free(paths_len);
	return (ants_per_node);
}
/*
** on recoit les paths sous forme d'indice, avec le score si on le multiplie par le nombre de chemin
** moins la taille du chemin on a le nb de fourmie que ce chemin va recevoir, et donc comme ca on a plus
** qu'a cree la colony dabord avec le premier chemins et sont nb de fourmie et ainsi de suite
** mais il ne faut pas oublier la diff, cad si 3 chemins et 5 fourmis y aura un cheins qui aura une fourmie en moins
*/
void assign_colony(t_env *env)
{
	int i;
	int *ants_per_node;
	int next_node;

	i = -1;
	(env->colony = (t_ant **)malloc(sizeof(t_ant *) * env->nb_ants))
	? 0 : perr(env, "Error: t_ant ** malloc failed");
	ants_per_node = get_ants_per_node(env);
	next_node = 0;
	while (++i < env->nb_ants)
	{
		printf("new ant #%d in colony: using node %d (path #%d)\n"
			, i, next_node, env->best_combo[next_node]);
		env->colony[i] = new_ant(env, env->paths[env->best_combo[next_node]], env->nb_rooms);
		ants_per_node[next_node]--;

		while (i != (env->nb_ants - 1))
		{
			next_node = (next_node == (env->best_flow - 1)) ? 0 : (next_node + 1);
			if (ants_per_node[next_node] != 0)
				break;
		}
	}
	free(ants_per_node);
	IS_SET_A ? put_ants(env) : 0;
}

void put_ant(t_env *env, t_ant *ant)
{
	if (ant && ant->path && ant->path->rooms && ant->path->current - 1 != 0)
	{
		// ((ant->path->current != ant->path->size) && (ant != env->colony[0]))
		// ? write(1, " ", 1) : 0;
		// (ant != env->colony[0] && ant->path->size == 2)
		if (env->new_line > 0)	
			write(1, " ", 1);
		else
			env->new_line++;
		write(1, "L", 1);
		plong(1, ant->n, '\0');
		write(1, "-", 1);
		(ant->path->rooms[ant->path->current - 1] != -1)
		? pstr(1, env->room_names[ant->path->rooms[ant->path->current - 1]], '\0')
		: perr(env, "Error: ant->path->current points to no room");
		// write(1, " ", 1);
	}
}

int room_id_error(t_env *env, int room_id)
{
	if (room_id < 0)
		return (-1);
		// perr(env, "Error: checked for business on a negative room_id");
	if (room_id > (env->nb_rooms - 1))
		return (1);
	return (0);
		// perr(env, "Error: checked for business on a not existing room_id");
}

int is_room_free(t_env *env, int room_id)
{
	int err;

	err = room_id_error(env, room_id);
	err == -1 ? perr(env, "Error: is_room_free called on a negative room_id") : 0;
	err == 1 ? perr(env, "Error: is_room_free called on an unknown room_id") : 0;
	if (room_id == 0 || room_id == 1)
		return (1);
	return (env->room_free[room_id]);
}

int set_room_busy(t_env *env, int room_id)
{
	int err;

	err = room_id_error(env, room_id);
	err == -1 ? perr(env, "Error: set_room_busy called on a negative room_id") : 0;
	err == 1 ? perr(env, "Error: set_room_busy called on an unknown room_id") : 0;
	if (room_id > 1)
	{
		env->room_free[room_id] = 0;
		return (1);
	}
	return (0);
}

int set_room_free(t_env *env, int room_id)
{
	int err;

	err = room_id_error(env, room_id);
	err == -1 ? perr(env, "Error: set_room_free called on a negative room_id") : 0;
	err == 1 ? perr(env, "Error: set_room_free called on an unknown room_id") : 0;
	if (room_id > 1)
	{
		env->room_free[room_id] = 1;
		return (1);
	}
	return (0);
}

int move_ant_forward(t_env *env, t_ant *ant)
{
	ant ? 0 : perr(env, "Error: tried to move non-existing ant");
	ant->path ? 0 : perr(env, "Error: ant has no path to follow");
	ant->path->size > 0 ? 0 : perr(env, "Error: ant path size <= 0");
	ant->path->rooms ? 0 : perr(env, "Error: ant path has no rooms");
	if (ant->path->current > ant->path->size)
	{
		printf("at colony[%d], path->current=%d, path->size=%d\n"
			, (ant->n - 1), ant->path->current, ant->path->size);
		perr(env, "Error: ant->path->current overflow");
	}
	if ((ant->path->current > 1) && ant->path->rooms[ant->path->current - 1] == 1)
		return (0);
	// printf("calling is_room_free() for colony[%d], (ant->path->current + 1) = %d, ant->path->rooms[ant->path->current + 1] = %d\n"
	// 	, (ant->n - 1), (ant->path->current + 1), ant->path->rooms[ant->path->current + 1]);
	// printf("ant->path->rooms[ant->path->current] = %d\n"
	// 	, ant->path->rooms[ant->path->current]);
	if (ant->path->current < ant->path->size
		&& is_room_free(env, ant->path->rooms[ant->path->current]))
	{
		if (ant->path->current > 0)
			set_room_free(env, ant->path->rooms[ant->path->current - 1]);
		set_room_busy(env, ant->path->rooms[ant->path->current]);
		ant->path->current++;
		!IS_SET_M ? put_ant(env, ant) : 0;
		if (ant->path->rooms[ant->path->current - 1] == 1)
			return (1);
	}
	return (0);
}

void move_colony(t_env *env)
{
	int i;
	int n_arrived;

	n_arrived = 0;
	assign_colony(env);
	// rounds = (env->nb_ants + path_len(env->paths[0], env->nb_rooms));
	// IS_SET_M ? 0 : write(1, "\n", 1);
	while (n_arrived < env->nb_ants && (i = -1))
	{
		env->new_line = 0;
		while (n_arrived < env->nb_ants && ++i < env->nb_ants)
		{
			n_arrived += move_ant_forward(env, env->colony[i]);
		}
		!IS_SET_M ? write(1, "\n", 1) : 0;
	}
}
