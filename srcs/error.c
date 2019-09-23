/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:54 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/17 12:39:53 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		put_usage(t_env *env)
{
	sp_putstr(1,
		"Usage: ./lem-in [OPTION]... [INPUT]\n"
		"       ./lem-in [OPTION]... < [FILE]\n\n"
		"  -u\tuncomment: hides comments on output\n"
		"  -m\tmute: hides execution output\n"
		"  -v\tverbose: displays solver full output\n"
		"  -r\trooms: displays room list\n"
		"  -l\tlinks: displays link matrix\n"
		"  -a\tants: displays colony details\n"
		// "  -s\tsolver: displays solution\n"
		, '\0');
	deinit_env(env);
	exit(0);
}

void		perr(t_env *env, const char *err_msg)
{
	/*!IS_SET_E ? sp_putstr(2, "Error", '\n') : */sp_putstr(2, err_msg, '\n');
	deinit_env(env);
	exit(1);
}

// void		sig_handler(int sig)
// {
// 	signal(sig, SIG_IGN);
// 	sp_putstr(2, ("Lem-in Force Quit\n"), '\0');
// 	exit(EXIT_FAILURE);
// }

int			anthill_complete(t_env *env)
{
	env->nb_ants <= 0 ? perr(env, "Error: no ants") : 0;
	!env->start ? perr(env, "Error: no start room") : 0;
	!env->end ? perr(env, "Error: no end room") : 0;
	return (1);
}
