/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 11:41:55 by paullaurent       #+#    #+#             */
/*   Updated: 2019/09/20 13:14:52 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_solut(t_solut *solut, int *ants_per_path)
{
	t_paths	*tmp_paths;
	t_link	*tmp_path;
    int     i;

	tmp_paths = solut->paths;
    i = 0;
    ft_printf("env->best_solut: \n");
	while (solut->paths)
	{
		ft_printf("path: %d\n", ++i);
		tmp_path = solut->paths->path;
		while (solut->paths->path)
		{
			if (solut->paths->path->adjacent->name)
				ft_printf("%s", solut->paths->path->adjacent->name);
			if (solut->paths->path->next)
				ft_printf("-");
			solut->paths->path = solut->paths->path->next;
		}
		solut->paths->path = tmp_path;
		ft_printf("\nlen = %d   ants_per_path: %d\n\n", solut->paths->len, ants_per_path[i - 1]);
		solut->paths = solut->paths->next;
	}
	solut->paths = tmp_paths;
}

void			print_rooms(t_graph *graph)
{
	t_graph	*tmp_g;

	tmp_g = graph;
	while (graph)
	{
		ft_printf("rooms: %s\n", graph->name);
		graph = graph->next;
	}
	graph = tmp_g;
}