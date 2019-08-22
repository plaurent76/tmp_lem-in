/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:16:19 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/22 12:16:21 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		store_line(t_env *env, char *s)
{
	static t_lines	*last = NULL;
	t_lines			*l;

	(s && *s) ? 0 : perr(env, "Error: no line to store");
	(l = (t_lines *)malloc(sizeof(t_lines)))
	? 0 : perr(env, "t_lines malloc failed");
	(l->txt = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2)))
	? 0 : perr(env, "char* malloc failed");
	l->txt[0] = '\0';
	sp_strcpy(&(l->txt[0]), s, '\0');
	env->first_line == NULL ? (env->first_line = l) : 0;
	l->next = NULL;
	if (last)
	{
		l->prev = last;
		last->next = l;
	}
	else
		l->prev = NULL;
	last = l;
}

void			put_lines(t_env *env)
{
	t_lines			*l;

	l = env->first_line;
	while (l && l->prev)
		l = l->prev;
	(l && l->txt) ? 0 : perr(env, "Error: no anthill to print");
	while (l)
	{
		if (IS_SET_U && l->txt[0] == '#'
			&& ft_strcmp(l->txt, "##start") && ft_strcmp(l->txt, "##end"))
		{
			l = l->next;
			continue;
		}
		sp_putstr(1, l->txt, '\n');
		l = l->next;
	}
}

void			free_lines(t_env *env)
{
	t_lines			*l;

	l = env->first_line;
	while (l && l->prev)
		l = l->prev;
	while (l && l->next)
	{
		l = l->next;
		(l->prev && l->prev->txt) ? free(l->prev->txt) : 0;
		l->prev ? free(l->prev) : 0;
	}
	(l && l->txt) ? free(l->txt) : 0;
	l ? free(l) : 0;
	env->first_line = NULL;
}

int				get_lines(t_env *env)
{
	char		input[10240];
	char		*p;
	char		c;
	int			i;
	int			handler;

	p = (char *)input;
	i = -1;
	while ((handler = read(0, &c, 1)) >= 0)
	{
		if (!handler)
			break ;
		p[++i] = c;
		if (c == 10)
		{
			p[i] = '\0';
			if (!*p || (*p && !interpret_line(env, p)))
				break ;
			store_line(env, p);
			i = -1;
		}
	}
	return (1);
}
