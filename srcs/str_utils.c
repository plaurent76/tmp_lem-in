/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:12:47 by plaurent          #+#    #+#             */
/*   Updated: 2019/09/29 17:38:17 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			sp_putstr(int fd, const char *s, char end)
{
	char *p;

	p = (char *)s;
	*s ? write(fd, s, ft_strlen(p)) : 0;
	end != 0 ? write(fd, &end, 1) : 0;
	return (1);
}

int			sp_putlong(int fd, long nb, char end)
{
	char c;

	if (nb < 0)
		write(fd, "-", 1);
	if ((nb = (nb < 0 ? -nb : nb)) >= 10)
		sp_putlong(fd, nb / 10, '\0');
	c = (nb % 10) + '0';
	write(fd, &c, 1);
	(end != 0) ? write(fd, &end, 1) : 0;
	return (1);
}

int			sp_strcpy(char *dest, const char *src, const char c)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = c;
	dest[++i] = '\0';
	return (1);
}

long		fatol(t_env *env, const char *str)
{
	long		nb;
	long		sign;

	while (*str && is_space(*str))
		++str;
	(*str) ? 0 : perr(env, "Error: fatol: nothing to parse");
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		++str;
	nb = 0;
	while (*str)
		is_digit(*str) ? nb = 10 * nb + (*(str++) - '0')
	: perr(env, "Error: expected digit only");
	(*str && nb == 0) ? perr(env, "Error: expected a number") : 0;
	(nb > 2147483647 || nb < -2147483647)
	? perr(env, "Error: expected an integer") : 0;
	return (nb * sign);
}
