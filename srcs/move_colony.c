/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_colony.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:16:32 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/29 14:49:07 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int *get_ants_per_path(t_env *env)
{
	int *ants_per_path;
	int i;
	int ants_left;
	t_paths	*tmp;

	(ants_per_path = alloc_array_int(env->best_flow, 0)) ? 0
	: perr(env, "Error: ants_per_node malloc failed");
	i = -1;
	tmp = env->best_solut->paths;
	ants_left = env->nb_ants;
	while (++i < env->best_flow && ants_left > 0)
	{
		if ((env->best_solut->score - (env->best_solut->paths->path->len - 1)) >= ants_left)
			ants_per_path[i] = ants_left;
		else if ((env->best_solut->score - (env->best_solut->paths->path->len - 1)) > 0)
			ants_per_path[i] = env->best_solut->score - (env->best_solut->paths->path->len - 1);
        ants_left -= ants_per_path[i];
		env->best_solut->paths = env->best_solut->paths->next;
	}
	env->best_solut->paths = tmp;
	i = 0;
	while (--ants_left >= 0)
	{
		if (ants_per_path[i] > 0)
		{
		ants_per_path[i]++;
		i = (i == (env->best_flow - 1)) ? 0 : (i + 1);
		}
	}
	(IS_SET_V) ? print_solut(env->best_solut, ants_per_path) : 0;
	return (ants_per_path);
}

void assign_colony(t_env *env)
{
	int i;
	int *ants_per_path;
	int next_node;
	t_paths	*tmp;

	i = -1;
	(env->colony = (t_ant **)malloc(sizeof(t_ant *) * env->nb_ants))
	? 0 : perr(env, "Error: t_ant ** malloc failed");
	ants_per_path = get_ants_per_path(env);
	next_node = 0;
	tmp = env->best_solut->paths;
	while (++i < env->nb_ants)
	{
		IS_SET_V ? ft_printf("new ant #%d in colony: using node %d\n"
			, i, next_node) : 0;
		env->colony[i] = new_ant(env, env->best_solut->paths->path);
		ants_per_path[next_node]--;
		while (i != (env->nb_ants - 1))
		{
			if (next_node == (env->best_flow - 1))
			{
				next_node = 0;
				env->best_solut->paths = tmp;
			}
			else
			{
				next_node++;
				env->best_solut->paths = env->best_solut->paths->next;
			}
			if (ants_per_path[next_node] != 0)
				break;
		}
	}
	env->best_solut->paths = tmp;
	free(ants_per_path);
}

void put_ant(t_env *env, t_ant *ant)
{
	if (ant && ant->path && ant->path->adjacent)
	{
		if (env->new_line > 0)	
			write(1, " ", 1);
		else
			env->new_line++;
		write(1, "L", 1);
		sp_putlong(1, ant->n, '\0');
		write(1, "-", 1);
		sp_putstr(1, ant->path->adjacent->name, '\0');
	}
}

int move_ant_forward(t_env *env, t_ant *ant)
{
    t_link   *tmp;

	if (ant->path->adjacent == env->end)
			return (0);
	ant ? 0 : perr(env, "Error: tried to move non-existing ant");
    ant->path ? 0 : perr(env, "Error: ant has no path to follow");
    tmp = ant->path;
	if (ant->path->next->adjacent->ant == 0)
	{
        ant->path = ant->path->next;
		if (ant->path->adjacent != env->end)
            ant->path->adjacent->ant = 1;
		!IS_SET_M ? put_ant(env, ant) : 0;
        tmp->adjacent->ant = 0;
		if (ant->path->adjacent == env->end)
			return (1);
    }
	return (0);
}

void move_colony(t_env *env)
{
	int i;
	int n_arrived;
	int	n_line;

	n_line = -1;
	n_arrived = 0;
	assign_colony(env);
	ft_putchar('\n');
	while (n_arrived < env->nb_ants && (i = -1))
	{
		env->new_line = 0;
		while (n_arrived < env->nb_ants && ++i < env->nb_ants)
		{
			n_arrived += move_ant_forward(env, env->colony[i]);
		}
		!IS_SET_M ? write(1, "\n", 1) : 0;
		n_line++;
	}
	IS_SET_V ? ft_printf ("nb_lines: %d", n_line) : 0;
}
