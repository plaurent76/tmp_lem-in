/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:18 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/23 11:34:36 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	g_ant_id = 0;

t_ant	*new_ant(t_env *env, t_link *path)
{
	t_ant		*a;

	(a = (t_ant *)malloc(sizeof(t_ant)))
	? 0 : perr(env, "t_ant malloc failed");
	a->path = path;
	a->n = ++g_ant_id;
	return (a);
}