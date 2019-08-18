/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:14 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:26:18 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			scmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int			pstr(int fd, const char *s, char end)
{
	char *p;

	p = (char *)s;
	*s ? write(fd, s, slen(p)) : 0;
	end != 0 ? write(fd, &end, 1) : 0;
	return (1);
}

int			plong(int fd, long nb, char end)
{
	char c;

	if (nb < 0)
		write(fd, "-", 1);
	if ((nb = (nb < 0 ? -nb : nb)) >= 10)
		plong(fd, nb / 10, '\0');
	c = (nb % 10) + '0';
	write(fd, &c, 1);
	(end != 0) ? write(fd, &end, 1) : 0;
	return (1);
}

int			scat(char *dest, const char *src, const char c)
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
