/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:03 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:26:04 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			spaces_in(const char *str)
{
	const char	*p = str;
	int			i;
	int			prev;

	prev = 1;
	i = 0;
	while (*p)
	{
		(is_space(*p) && !prev) ? i++ : 0;
		prev = is_space(*p) ? 1 : 0;
		p++;
	}
	return (prev ? (i - 1) : i);
}
