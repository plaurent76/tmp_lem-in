/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:18 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:12:19 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	g_ant_id = 0;

t_ant	*new_ant(t_env *env, int *path, int path_size)
{
	t_ant		*a;

	(a = (t_ant *)malloc(sizeof(t_ant)))
	? 0 : perr(env, "t_ant malloc failed");
	a->path = new_path(env, path, path_size);
	a->n = ++g_ant_id;
	return (a);
}

void	put_ants(t_env *env)
{
	int i;

	(env->colony && env->nb_ants > 0) ? 0 : perr(env, "Error: no colony");
	i = -1;
	sp_putstr(1, "Colony size:", ' ');
	sp_putlong(1, env->nb_ants, '\n');
	if (IS_SET_V)
	{
		sp_putstr(1, "Ants' paths:", '\n');
		while (++i < env->nb_ants)
		{
			sp_putstr(1, "#", '\0');
			sp_putlong(1, i, ' ');
			put_ant_path(env->colony[i]->path);
		}
	}
}

void	del_ant(t_env *env, t_ant *ant)
{
	if (!ant)
		return ;
	(ant->path && ant->path->rooms)
	? set_room_free(env, ant->path->rooms[ant->path->current - 1]) : 0;
	del_ant_path(ant->path);
	free(ant);
	ant = NULL;
	--g_ant_id;
}
