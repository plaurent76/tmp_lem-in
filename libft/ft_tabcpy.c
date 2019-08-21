/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:13:35 by eviana            #+#    #+#             */
/*   Updated: 2019/07/23 17:28:29 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_tabcpy(int *src, size_t size)
{
	int		*copy;
	size_t  i;

    i = 0;
    if (!(copy = (int*)malloc(sizeof(int) * size)))
        return (NULL);
    while (i < size)
    {
        copy[i] = src[i];
        i++;
    }
    return (copy);	
}