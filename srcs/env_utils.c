/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:07 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/29 12:59:04 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_colony(t_env *env)
{
	int i;

	i = env->nb_ants;
	if (env->colony)
		while (--i >= 0)
			env->colony[i] ? del_ant(env->colony[i]) : 0;
	free(env->colony);
	env->colony = NULL;
}

static void	free_graph(t_graph **g)
{
	t_graph	*tmp;

	if (g)
	{
		while (*g)
		{
			tmp = (*g)->next;
			ft_strdel(&(*g)->name);
			del_path(&(*g)->link);
			free(*g);
			*g = NULL;
			(*g) = tmp;
		}
	}
}

static void	free_paths(t_paths **p)
{
	if (!p || !(*p))
		return ;
	if ((*p)->next != NULL)
		free_paths(&(*p)->next);
	if (p)
	{
		del_path(&(*p)->path);
		free(*p);
		*p = NULL;
	}
}

static void	free_solut(t_solut **s)
{
	t_solut	*tmp;

	if (s)
	{
		while (*s)
		{
			tmp = (*s)->next;
			free_paths(&(*s)->paths);
			free(*s);
			*s = NULL;
			(*s) = tmp;
		}
	}
}

void			init_env(t_env *env)
{
	env->t_len = 0;
	env->graph = NULL;
	env->start = NULL;
	env->end = NULL;
	env->end_found = 0;
	env->solut = NULL;
	env->best_solut = NULL;
	env->best_score = 10000;
	env->best_flow = 1;
	env->start = NULL;
	env->end = NULL;
	env->nb_ants = 0;
	env->colony = NULL;
	env->option = 0;
	env->first_line = NULL;
	env->nb_rooms = 0;
	env->new_line = 0;
	env->flow_max = 0;
}

void			deinit_env(t_env *env)
{
	env->start = NULL;
	free_graph(&env->graph);
	free_solut(&env->solut);
	free_lines(env);
	free_colony(env);
}
