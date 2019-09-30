/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:43 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 15:29:05 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_start_end(t_env *env)
{
	int i;

	put_lines(env);
	i = 0;
	ft_putchar('\n');
	while (i < env->nb_ants)
	{
		ft_printf("L%d-%s", i + 1, env->end->name);
		if (i != env->nb_ants - 1)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	deinit_env(env);
	exit(EXIT_SUCCESS);
}

static void	make_magic_happen(t_env *env)
{
	if (env->end_found <= 1)
		perr(env, "Error: end not found or no link");
	if (link_search(env->start, env->end->name))
		print_start_end(env);
	anthill_complete(env);
	if ((env->flow_max = ed_karp(env)) == 0)
		perr(env, "Error: no path found");
	!IS_SET_M ? put_lines(env) : 0;
	IS_SET_R ? print_rooms(env->graph) : 0;
	move_colony(env);
	deinit_env(env);
	exit(EXIT_SUCCESS);
}

static int	get_option(t_env *env, char *av, int i)
{
	while (av[++i])
	{
		if ((av[i] != 'm' && av[i] != 'r' && av[i] != 'v' && av[i] != 'h'))
			perr(env, "Error: invalid option");
		else if (((av[i] == 'm' && IS_SET_M)
			|| (av[i] == 'v' && IS_SET_V) || (av[i] == 'r' && IS_SET_R)
			|| (av[i] == 'h' && IS_SET_H)))
			perr(env, "Error: duplicate option");
		(av[i] == 'h') ? SET_H : 0;
		(av[i] == 'm') ? SET_M : 0;
		(av[i] == 'r') ? SET_R : 0;
		(av[i] == 'v') ? SET_V : 0;
	}
	return (active_bits(env->option));
}

static void	init_env(t_env *env)
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
	env->new_line = 0;
	env->flow_max = 0;
}

int			main(int ac, char **av)
{
	t_env	env;
	int		i;

	init_env(&env);
	i = 0;
	while (++i < ac && av[i] && av[i][0] == '-')
	{
		get_option(&env, av[i], 0);
		(env.option & (1 << 7)) ? put_usage(&env) : 0;
	}
	get_lines(&env);
	make_magic_happen(&env);
	return (1);
}
