/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:31:17 by plaurent          #+#    #+#             */
/*   Updated: 2019/10/07 11:56:09 by paullaurent      ###   ########.fr       */
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
