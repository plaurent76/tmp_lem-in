/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_colony.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:16:32 by plaurent          #+#    #+#             */
/*   Updated: 2019/10/07 14:08:13 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_color(t_ant *ant)
{
	int		id;

	id = ant->n;
	id++;
	while (id > 8)
		id -= 8;
	if (id == 1)
		ft_printf("\033[01;31mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 2)
		ft_printf("\033[01;32mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 3)
		ft_printf("\033[01;33mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 4)
		ft_printf("\033[01;34mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 5)
		ft_printf("\033[01;35mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 6)
		ft_printf("\033[01;36mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 7)
		ft_printf("\033[01;37mL%d-%s", ant->n, ant->path->adjacent->name);
	else if (id == 8)
		ft_printf("\033[01;0mL%d-%s", ant->n, ant->path->adjacent->name);
}

void		put_ant(t_env *env, t_ant *ant)
{
	if (ant && ant->path && ant->path->adjacent)
	{
		if (env->new_line != 0)
			write(1, " ", 1);
		else
			env->new_line = 1;
		write(1, "L", 1);
		sp_putlong(1, ant->n, '\0');
		write(1, "-", 1);
		ft_putstr(ant->path->adjacent->name);
	}
}

void		put_ant_color(t_env *env, t_ant *ant)
{
	if (ant && ant->path && ant->path->adjacent)
	{
		if (env->new_line != 0)
			write(1, " ", 1);
		else
			env->new_line = 1;
		print_color(ant);
	}
}

int			move_ant_forward(t_env *env, t_ant *ant)
{
	t_link	*tmp;

	if (ant->path->adjacent == env->end)
		return (0);
	ant ? 0 : perr(env, "Error: tried to move non-existing ant");
	ant->path ? 0 : perr(env, "Error: ant has no path to follow");
	tmp = ant->path;
	if (ant->path->next->adjacent->ant == 0)
	{
		ant->path = ant->path->next;
		if (ant->path->adjacent != env->end)
			ant->path->adjacent->ant = 1;
		if (!IS_SET_M)
			!IS_SET_C ? put_ant(env, ant) : put_ant_color(env, ant);
		tmp->adjacent->ant = 0;
		if (ant->path->adjacent == env->end)
			return (1);
	}
	return (0);
}

void		move_colony(t_env *env)
{
	int i;
	int n_arrived;
	int	n_line;

	n_line = 0;
	n_arrived = 0;
	assign_colony(env);
	!IS_SET_M ? ft_putchar('\n') : 0;
	while (n_arrived < env->nb_ants && (i = -1))
	{
		env->new_line = 0;
		while (n_arrived < env->nb_ants && ++i < env->nb_ants)
			n_arrived += move_ant_forward(env, env->colony[i]);
		!IS_SET_M ? write(1, "\n", 1) : 0;
		n_line++;
	}
	IS_SET_C ? ft_printf("\033[01;0m") : 0;
	IS_SET_V ? ft_printf("nb_lines: %d\n", n_line) : 0;
}
