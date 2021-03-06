/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:11:54 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 14:40:36 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		put_usage(t_env *env)
{
	sp_putstr(1,
		"Usage: ./lem-in [OPTION]... [INPUT]\n"
		"       ./lem-in [OPTION]... < [FILE]\n\n"
		"  -m\tmute: hides execution output\n"
		"  -v\tverbose: displays solver full output\n"
		"  -r\trooms: displays room list\n"
		, '\0');
	deinit_env(env);
	exit(0);
}

void		perr(t_env *env, const char *err_msg)
{
	sp_putstr(2, err_msg, '\n');
	deinit_env(env);
	exit(1);
}

int			anthill_complete(t_env *env)
{
	env->nb_ants <= 0 ? perr(env, "Error: no ants") : 0;
	!env->start ? perr(env, "Error: no start room") : 0;
	!env->end ? perr(env, "Error: no end room") : 0;
	return (1);
}
