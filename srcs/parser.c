/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:12 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 16:25:29 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_ants(t_env *env, const char *p)
{
	env->nb_ants = fatol(env, p);
	if (env->nb_ants > 2147483647 || env->nb_ants <= 0)
		perr(env, "Error: expected a positive ant colony size");
	return (1);
}

static int		get_room(t_env *env, const char *p, int x, int y, int state)
{
	int		i;
	char	tmp[3][256];

	i = -1;
	while (!p[++i] || !is_space(p[i]))
		if (!p[i] || (p[0] == 'L') || (p[i] == '-'))
			return (0);
		else
			tmp[0][i] = p[i];
	tmp[0][i] = '\0';
	while (!p[++i] || !is_space(p[i]))
		if (!p[i] || !is_digit(p[i]))
			return (0);
		else
			tmp[1][++x] = p[i];
	tmp[1][++x] = '\0';
	while ((p[++i]))
		if (!is_digit(p[i]))
			return (0);
		else
			tmp[2][++y] = p[i];
	tmp[2][++y] = '\0';
	new_room(env, tmp[0], fatol(env, tmp[1]), fatol(env, tmp[2]), state);
	return (1);
}

static int		get_link(t_env *env, const char *p, int i, int j)
{
	t_room	*room1;
	t_room	*room2;
	char	tmp[256];

	// ft_printf("un lien");
	while (!p[++i] || p[i] != '-')
		if (!p[i] || is_space(p[i]))
			return (0);
		else
			tmp[i] = p[i];
	tmp[i] = '\0';
	room1 = str_to_room(env, tmp);
	while (p[++i])
		if (is_space(p[i]))
			return (0);
		else
			tmp[++j] = p[i];
	tmp[++j] = '\0';
	room2 = str_to_room(env, tmp);
	new_link(env, room1, room2);
	// ft_printf("test");
	return (1);
}

static int		check_room(t_env *env, const char *p)
{
	if ((!env->start || !env->end))
		perr(env, "Error: incomplete room list or invalid room name");
	(!get_link(env, p, -1, -1)) ? perr(env, "Error: wrong input") : 0;
	return (1);
}

int				interpret_line(t_env *env, const char *p)
{
	static int state = 0;

	// sp_putlong(1, state, '\n');
	if (state == 0)
	{
		if (p[0] == '#' && ft_strcmp(p, "##start") && ft_strcmp(p, "##end"))
			return ((1));
		return ((get_ants(env, p) ? (state = 1) : 0));
	}
	if (!p || (p[0] && p[0] == '#' && ft_strcmp(p, "##start") && ft_strcmp(p, "##end")))
		return (1);
	if (!ft_strcmp(p, "##start") || !ft_strcmp(p, "##end"))
	{
		((!ft_strcmp(p, "##start") && env->start) || (!ft_strcmp(p, "##end") && env->end))
		? perr(env, "Error: duplicate command") : 0;
		return ((state = (!ft_strcmp(p, "##start") ? 2 : 3)));
	}
	if (state == 4)
	{
		// ft_printf("avant get_link");
		return ((get_link(env, p, -1, -1) ? 4 : 0));
	}
	if (!(get_room(env, p, -1, -1, state)) && check_room(env, p))
		return ((state = 4));
	state == 2 ? (env->start = env->last_parsed_room->room) : 0;
	state == 3 ? (env->end = env->last_parsed_room->room) : 0;
	return ((state = 1));
}