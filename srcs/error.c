/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:37 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:38 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		put_usage(t_env *env)
{
	pstr(1, "Usage: lem-in [OPTION]\n"
		"  -u\tuncomment: hides comments on output\n"
		"  -m\tmute: hides execution output\n"
		"  -v\tverbose: further info, use with [rla]\n"
		"  -r\trooms: displays room list\n"
		"  -l\tlinks: displays link list\n"
		"  -a\tants: displays colony\n"
		"  -s\tsolver: displays solution\n"
		, '\0');
	deinit_env(env);
	exit(EXIT_SUCCESS);
}

void		put_error(t_env *env, const char *err_msg)
{
	IS_SET_E ? pstr(2, err_msg, '\n') : pstr(2, "Error", '\n');
	deinit_env(env);
	exit(EXIT_FAILURE);
}

void		sig_handler(int sig)
{
	signal(sig, SIG_IGN);
	pstr(2, ("Lem-in Force Quit\n"), '\0');
	exit(EXIT_FAILURE);
}

int			anthill_complete(t_env *env)
{
	t_parsed_room *parsed;

	env->nb_ants <= 0 ? put_error(env, "Error: no ants") : 0;
	!env->start ? put_error(env, "Error: no start room") : 0;
	!env->end ? put_error(env, "Error: no end room") : 0;
	parsed = R1;
	if (!(parsed && parsed->room && parsed->room->link))
		put_error(env, "Error: incomplete anthill");
	return (1);
}
