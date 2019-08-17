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
	int		n_c;
	int		i;
	int		size;
	int		nb_ant_p;
	int		path;

	i = -1;
	size = 0;
	nb_ant_p = 0;
	n_c = 0;
	while (env->paths[0][size] != 1)
		size++;
	while (n_c < env->flow_max && env->best_combo[n_c] != -1)
		n_c++;
	(env->colony = (t_ant **)malloc(sizeof(t_ant *) * env->nb_ants))
	? 0 : put_error(env, "Error: t_ant ** malloc failed");
	/*
	** on recoit les paths sous forme d'indice, avec le score si on le multiplie par le nombre de chemin
	** moins la taille du chemin on a le nb de fourmie que ce chemin va recevoir, et donc comme ca on a plus
	** qu'a cree la colony dabord avec le premier chemins et sont nb de fourmie et ainsi de suite
	** mais il ne faut pas oublier la diff, cad si 3 chemins et 5 fourmis y aura un cheins qui aura une fourmie en moins
	*/
	while (++i < env->nb_ants)
	{
		if (nb_ant_p == 0)
		{
			
		}
		env->colony[i] = new_ant(env, env->paths[0], size);
	}
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
	rounds = (env->nb_ants + path_len(env->paths[0], env->nb_rooms));
	IS_SET_M ? 0 : write(1, "\n", 1);
	while (++i < rounds)
	{
		j = -1;
		while (++j < env->nb_ants)
			move_ant_forward(env, env->colony[j]);
		(i < (rounds - 1) && path_len(env->paths[0], env->nb_rooms) != 2 && (!IS_SET_M || IS_SET_S))
		? write(1, "\n", 1) : 0;
	}
	(path_len(env->paths[0], env->nb_rooms) == 2 && (!IS_SET_M || IS_SET_S)) ? write(1, "\n", 1) : 0;
}
