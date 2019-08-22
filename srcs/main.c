/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:43 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 15:21:58 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// map invalid command: il faut detecter que qd ## c est une commande qui peuvent etre invalid
// map startisend a faire gaffe

void			flag_v(t_env *env)
{
		int i;

// print valid paths:
		ft_printf("found %d valid paths:\n", env->nb_valid);
		print_matrix_int(env->paths, env->nb_rooms, env->nb_valid);
		ft_printf("\n");
		ft_printf("env->node_exploration finished:\n\n node #\t| room\t| n_paths\n--------------------------\n");
		print_matrix_int(env->node_exploration, 2, env->flow_start_max);
		ft_printf("\n");
		ft_printf("optimal combo found:\nenv->best_score: %d\nenv->best_flow: %d\nenv->best_combo:\n"
			, env->best_score, env->best_flow);
		print_array_int(env->best_combo, env->best_flow);
		ft_printf("env->best_combo: paths:\n");
		i = -1;
		while (++i < env->flow_max && env->best_combo[i] != -1)
			print_array_int(env->paths[env->best_combo[i]], env->nb_rooms);
}

static void		make_magic_happen(t_env *env)
{
	anthill_complete(env);
	prepare_env(env);
	solver(env);
	combo_optimal(env);
	if (IS_SET_V)
		flag_v(env);
	!IS_SET_M ?	put_lines(env) : 0;
	// IS_SET_R ? put_parsed_rooms(env) : 0;
	// IS_SET_L ? put_parsed_links(env) : 0;
	IS_SET_R ? put_rooms(env) : 0;
	IS_SET_L ? put_links(env) : 0;
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
		//ajouter les autres options
	}
	get_lines(&env);
	make_magic_happen(&env);
	return (1);
}
