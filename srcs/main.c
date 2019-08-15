/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:46 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/24 21:13:28 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		make_magic_happen(t_env *env)
{
	anthill_complete(env);
	genetic_solve(env);
	combo_optimal(env);
	//IS_SET_M ? 0 : put_lines(env);
	//IS_SET_R ? put_rooms(env) : 0;
	//IS_SET_L ? put_links(env) : 0;
	//IS_SET_S ? put_fwinfo(env) : 0;
	//move_colony(env);
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
			put_error(env, "Error: invalid option");
		else if ((av[i] == 'u' && IS_SET_U) || (av[i] == 'm' && IS_SET_M)
			|| (av[i] == 'a' && IS_SET_A) || (av[i] == 'l' && IS_SET_L)
			|| (av[i] == 'r' && IS_SET_R) || (av[i] == 's' && IS_SET_S)
			|| (av[i] == 'v' && IS_SET_V) || (av[i] == 'h' && IS_SET_H)
			|| (av[i] == 'e' && IS_SET_E))
			put_error(env, "Error: duplicate option");
		(av[i] == 'u') ? SET_U : 0;
		(av[i] == 'm') ? SET_M : 0;
		(av[i] == 'a') ? SET_A : 0;
		(av[i] == 'l') ? SET_L : 0;
		(av[i] == 'r') ? SET_R : 0;
		(av[i] == 's') ? SET_S : 0;
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

	signal(SIGINT, sig_handler);
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
