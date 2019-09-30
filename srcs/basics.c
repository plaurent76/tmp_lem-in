/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:13:57 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/30 10:27:08 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_space(const char c)
{
	return ((c < 14 && c > 7) || c == 32);
}

int		is_digit(const char c)
{
	return ((c >= '0' && c <= '9') ? 1 : 0);
}

int		active_bits(int c)
{
	int bits;

	bits = 0;
	while (c > 0)
	{
		if ((c & 1) == 1)
			bits++;
		c >>= 1;
	}
	return (bits);
}
