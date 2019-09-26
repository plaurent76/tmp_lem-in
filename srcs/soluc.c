/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soluc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:21:32 by paullaurent       #+#    #+#             */
/*   Updated: 2019/09/26 19:21:46 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_to_paths(t_paths **paths, t_paths *new)
{
	t_paths	*tmp;

	tmp = (*paths);
	if (*paths && paths)
	{
		while ((*paths)->next)
			(*paths) = (*paths)->next;
		(*paths)->next = new;
		(*paths) = tmp;
	}
	else
		*paths = new;
}

t_paths     *extract_paths(t_env *env)
{
    t_paths     *new_paths;
    t_link      *new_p;

    new_paths = NULL;
    while ((new_p = extract_path(env, NULL, env->start, env->start)))
    {
        env->end->visited = 0;
        env->t_len += new_p->len;
        add_to_paths(&new_paths, new_path(env, new_p));
    }
    return (new_paths);
}

t_solut     *new_solut(t_env *env, t_paths *paths, int flow_max)
{
    t_solut     *tmp;

    if (!(tmp = (t_solut*)malloc(sizeof(t_solut))))
        perr(env, "Error: malloc solut failed");
    tmp->len = flow_max;
    tmp->paths = paths;
    tmp->score = 0;
    tmp->next = NULL;
    return (tmp);
}

void        extract_solut(t_env *env, int flow_max)
{
    t_solut     *tmp;

    tmp = env->solut;
    if (env->best_score)
		ft_printf("score\n");
    if (env->solut)
    {
        while (env->solut)
            env->solut = env->solut->next;
        env->solut = new_solut(env, extract_paths(env), flow_max);
        env->solut->score = (((env->t_len + env->nb_ants - 1) / (env->solut->len)) + 0.999999f);
        if (env->solut->len <= 3 || env->best_score > env->solut->score)
        {
            env->best_score = env->solut->score;
            env->best_solut = env->solut;
            env->best_flow = flow_max;
        }
        env->solut = tmp;
    }
    else
    {
        env->solut = new_solut(env, extract_paths(env), flow_max);
        if (env->nb_ants)
		    ft_printf("WUUUUUT %d\n", env->solut->score);
            ft_printf("t_len: %d", env->t_len);
        env->solut->score = (env->t_len + env->nb_ants - 1) / env->solut->len;
		    ft_printf("WUUUUUT %d\n", env->solut->score);
        env->best_score = env->solut->score;
        env->best_solut = env->solut;
        env->best_flow = flow_max;
    }
    env->t_len = 0;
    if (env->best_solut->len)
		ft_printf("best_solut\n");
	if (env->best_solut->paths)
		ft_printf("paths\n");
	if (env->best_score)
		ft_printf("score\n");
	if (env->best_solut->paths->len)
		ft_printf("paths->len\n");
}