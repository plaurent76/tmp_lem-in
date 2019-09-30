/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:07 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 17:20:39 by plaurent         ###   ########.fr       */
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

static void		free_graph(t_graph **graph)
{
	t_graph	*tmp;

	if (graph)
	{
		while (*graph)
		{
			tmp = (*graph)->next;
			ft_strdel(&(*graph)->name);
			del_path(&(*graph)->link);
			free(*graph);
			*graph = NULL;
			(*graph) = tmp;
		}
	}
}

static void		free_paths(t_paths **paths)
{
	t_paths	*tmp;

	if (paths)
	{
		while (*paths)
		{
			tmp = (*paths)->next;
			del_path(&(*paths)->path);
			free(*paths);
			*paths = NULL;
			(*paths) = tmp;
		}
	}
}

static void		free_solut(t_solut **solut)
{
	t_solut	*tmp;

	if (solut)
	{
		while (*solut)
		{
			tmp = (*solut)->next;
			free_paths(&(*solut)->paths);
			free(*solut);
			*solut = NULL;
			(*solut) = tmp;
		}
	}
}

void			deinit_env(t_env *env)
{
	env->start = NULL;
	free_graph(&env->graph);
	free_solut(&env->solut);
	free_lines(env);
	free_colony(env);
}
