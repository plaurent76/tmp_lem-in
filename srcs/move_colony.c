/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_colony.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:55 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:58 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		assign_colony(t_env *env)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (env->paths[0][size] != -1)
		size++;
	(env->colony = (t_ant **)malloc(sizeof(t_ant *) * env->nb_ants))
	? 0 : put_error(env, "Error: t_ant ** malloc failed");
	while (++i < env->nb_ants)
		// change l'itinéraire env->fw en fonction de l'algo (combo paths)
		env->colony[i] = new_ant(env, env->paths[0], size);
	//IS_SET_A ? put_ants(env) : 0;
}

void			put_ant(t_env *env, t_ant *ant)
{
	if (ant && ant->path)
	{
		((ant->path->current != ant->path->size) && (ant != env->colony[0]))
		? write(1, " ", 1) : 0;
		(ant != env->colony[0] && ant->path->size == 2)
		? write(1, " ", 1) : 0;
		write(1, "L", 1);
		plong(1, ant->n, '\0');
		write(1, "-", 1);//il faut cree le tab qui va avoir tout les noms des rooms en fonction des id
		ant->path->rooms[ant->path->current] != -1
		? plong(1, ant->path->rooms[ant->path->current], '\0')
		: 0;
	}
}

int				move_ant_forward(t_env *env, t_ant *ant)
{
	ant ? 0 : put_error(env, "Error: tried to move non-existing ant");
	ant->path ? 0 : put_error(env, "Error: ant has no path to follow");
	ant->path->size > 0 ? 0 : put_error(env, "Error: ant path size <= 0");
	ant->path->rooms[ant->path->current] >= 0 ?
	0 : put_error(env, "Error: could not locate ant");
	if ((ant->path->current + 1) <= ant->path->size
		&& env->room_free[ant->path->rooms[ant->path->current + 1]])
	{
		env->room_free[ant->path->rooms[ant->path->current]] = 1;
		env->room_free[ant->path->rooms[ant->path->current + 1]] = 0;
		ant->path->current++;
		put_ant(env, ant);
		// ant->path->room->ant = (ant->path->room == env->end) ? NULL : ant;
		(IS_SET_M && !IS_SET_S) ? 0 : put_ant(env, ant);
		return (1);
	}
	return (0);
}

void			move_colony(t_env *env)
{
	int		i;
	int		j;
	int		rounds;

	i = -1;
	assign_colony(env);
	rounds = (env->nb_ants + path_len(env->paths[0]));
	IS_SET_M ? 0 : write(1, "\n", 1);
	while (++i < rounds)
	{
		j = -1;
		while (++j < env->nb_ants)
			move_ant_forward(env, env->colony[j]);
		(i < (rounds - 1) && path_len(env->paths[0]) != 2 && (!IS_SET_M || IS_SET_S))
		? write(1, "\n", 1) : 0;
	}
	(path_len(env->paths[0]) == 2 && (!IS_SET_M || IS_SET_S)) ? write(1, "\n", 1) : 0;
}
