/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:37 by pde-rent          #+#    #+#             */
/*   Updated: 2019/08/21 14:04:29 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		put_usage(t_env *env)
{
	pstr(1,
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
	exit(EXIT_SUCCESS);
}

void		perr(t_env *env, const char *err_msg)
{
	/*!IS_SET_E ? pstr(2, "Error", '\n') : */pstr(2, err_msg, '\n');
	deinit_env(env);
	exit(EXIT_FAILURE);
}

// void		sig_handler(int sig)
// {
// 	signal(sig, SIG_IGN);
// 	pstr(2, ("Lem-in Force Quit\n"), '\0');
// 	exit(EXIT_FAILURE);
// }

int			anthill_complete(t_env *env)
{
	t_parsed_room *parsed;

	env->nb_ants <= 0 ? perr(env, "Error: no ants") : 0;
	!env->start ? perr(env, "Error: no start room") : 0;
	!env->end ? perr(env, "Error: no end room") : 0;
	parsed = R1;
	if (!(parsed && parsed->room && parsed->room->link))
		perr(env, "Error: incomplete anthill");
	return (1);
}
