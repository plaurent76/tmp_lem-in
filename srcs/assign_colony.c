/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colony.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:27:10 by plaurent          #+#    #+#             */
/*   Updated: 2019/10/08 12:00:48 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	empty_ants_left(t_env *env, int *ants_per_path, int ants_left)
{
	int i;

	i = 0;
	while (ants_left > 0)
	{
		if (ants_per_path[i] > 0)
		{
			ants_left--;
			ants_per_path[i]++;
			i = (i == (env->best_flow - 1)) ? 0 : (i + 1);
		}
		else
			i = (i == (env->best_flow - 1)) ? 0 : (i + 1);
	}
}

static int	*assign(t_env *env, int *app, int ants_left)
{
	int		i;
	int		j;
	int		len;
	t_paths	*tmp;

	i = -1;
	j = 0;
	while (ants_left > 0)
	{
		tmp = env->best_solut->paths;
		len = 0;
		j = 0;
		while (++i < env->best_flow)
		{
			if (len == 0 || (len > (tmp->path->len + app[i])))
			{
				j = i;
				len = tmp->path->len;
			}
			tmp = tmp->next;
		}
		app[j]++;
		ants_left--;
	}
	return (app);
}

static int	*get_ants_per_path(t_env *env)
{
	int		*ants_per_path;
	int		i;
	int		ants_left;
	t_paths	*tmp;

	(ants_per_path = alloc_array_int(env->best_flow, 0)) ? 0
		: perr(env, "Error: ants_per_node malloc failed");
	i = -1;
	tmp = env->best_solut->paths;
	ants_left = env->nb_ants;
	if (ants_left < env->best_flow)
		return (assign(env, ants_per_path, ants_left));
	while (++i < env->best_flow && ants_left > 0)
	{
		if ((env->best_solut->score - (tmp->path->len - 1)) >= ants_left)
			ants_per_path[i] = ants_left;
		else if ((env->best_solut->score - (tmp->path->len - 1)) > 0)
			ants_per_path[i] = env->best_solut->score - (tmp->path->len - 1);
		ants_left -= ants_per_path[i];
		tmp = tmp->next;
	}
	empty_ants_left(env, ants_per_path, ants_left);
	(IS_SET_V) ? print_solut(env->best_solut, ants_per_path) : 0;
	return (ants_per_path);
}

static int	next_path(t_env *env, int id_path, t_paths *tmp, int *app)
{
	while (1)
	{
		if (id_path == (env->best_flow - 1) && !(id_path = 0))
			env->best_solut->paths = tmp;
		else
		{
			id_path++;
			env->best_solut->paths = env->best_solut->paths->next;
		}
		if (app[id_path] != 0)
			return (id_path);
	}
	return (id_path);
}

void		assign_colony(t_env *env)
{
	int		i;
	int		*ants_per_path;
	int		id_path;
	t_paths	*tmp;

	i = -1;
	(env->colony = (t_ant **)malloc(sizeof(t_ant *) * env->nb_ants))
		? 0 : perr(env, "Error: t_ant ** malloc failed");
	ants_per_path = get_ants_per_path(env);
	id_path = 0;
	tmp = env->best_solut->paths;
	while (i < env->nb_ants - 1)
	{
		if (ants_per_path[id_path] > 0)
		{
			env->colony[++i] = new_ant(env, env->best_solut->paths->path);
			ants_per_path[id_path]--;
			IS_SET_V ? ft_printf("ant #%d using node %d\n", i, id_path) : 0;
		}
		if (i < (env->nb_ants - 1))
			id_path = next_path(env, id_path, tmp, ants_per_path);
	}
	env->best_solut->paths = tmp;
	free(ants_per_path);
}
