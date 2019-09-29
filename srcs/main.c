/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:43 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/29 14:48:40 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_start_end(t_env *env)
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

static void		make_magic_happen(t_env *env)
{
	if (env->end_found <= 1)
		perr(env, "Error: end note found or no link");
	if (link_search(env->start, env->end->name))
		print_start_end(env);
	anthill_complete(env);
	if ((env->flow_max = ed_karp(env)) == 0)
		perr(env, "Error: no path found");
	!IS_SET_M ?	put_lines(env) : 0;
	IS_SET_R ? print_rooms(env->graph) : 0;
	move_colony(env);
	deinit_env(env);
	exit(EXIT_SUCCESS);
}

static int		get_option(t_env *env, char *av, int i)
{
	while (av[++i])
	{
		if ((av[i] != 'u' && av[i] != 'm' && av[i] != 'a' && av[i] != 'l'
			&& av[i] != 'r' && av[i] != 's' && av[i] != 'v' && av[i] != 'h'
			&& av[i] != 'e'))
			perr(env, "Error: invalid option");
		else if ((av[i] == 'u' && IS_SET_U) || (av[i] == 'm' && IS_SET_M)
			|| (av[i] == 'a' && IS_SET_A) || (av[i] == 'l' && IS_SET_L)
			|| (av[i] == 'v' && IS_SET_V) || (av[i] == 'h' && IS_SET_H)
			|| (av[i] == 'e' && IS_SET_E) || (av[i] == 'r' && IS_SET_R))
			perr(env, "Error: duplicate option");
		(av[i] == 'u') ? SET_U : 0;
		(av[i] == 'm') ? SET_M : 0;
		(av[i] == 'a') ? SET_A : 0;
		(av[i] == 'l') ? SET_L : 0;
		(av[i] == 'r') ? SET_R : 0;
		(av[i] == 'v') ? SET_V : 0;
		(av[i] == 'h') ? SET_H : 0;
		(av[i] == 'e') ? SET_E : 0;
	}
	return (active_bits(env->option));
}

int				main(int ac, char **av)
{
	t_env	env;
	int		i;

	//signal(SIGINT, sig_handler);
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
