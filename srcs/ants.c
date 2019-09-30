/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:31:17 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 14:31:24 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*new_ant(t_env *env, t_link *path)
{
	t_ant		*a;
	static int	ant_id = 0;

	(a = (t_ant *)malloc(sizeof(t_ant)))
	? 0 : perr(env, "t_ant malloc failed");
	a->path = path;
	a->n = ++ant_id;
	return (a);
}

void	del_ant(t_ant *ant)
{
	if (!ant)
		return ;
	free(ant);
	ant = NULL;
}
