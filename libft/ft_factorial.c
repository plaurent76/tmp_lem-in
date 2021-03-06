/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:44:54 by plaurent          #+#    #+#             */
/*   Updated: 2019/05/29 18:44:56 by plaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_factorial(int nb)
{
	if ((nb < 0) || (nb > 12))
		return (0);
	else if (nb == 0)
		return (1);
	return (nb * ft_factorial(nb - 1));
}
