/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soluc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:21:32 by paullaurent       #+#    #+#             */
/*   Updated: 2019/09/25 11:07:01 by paullaurent      ###   ########.fr       */
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

t_paths     *extract_paths(t_env *env, int *t_len)
{
    t_paths     *new_paths;
    t_link      *new_p;

    new_paths = NULL;
    while ((new_p = extract_path(env, NULL, env->start, env->start)))
    {
        env->end->visited = 0;
        *t_len += new_p->len;
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
    tmp->next = NULL;
    return (tmp);
}

void        extract_solut(t_env *env, int flow_max)
{
    t_solut     *tmp;
    int         t_len;

    t_len = 0;
    tmp = env->solut;
    if (env->solut)
    {
        while (env->solut)
            env->solut = env->solut->next;
        env->solut = new_solut(env, extract_paths(env, &t_len), flow_max);
        if (env->best_score == 0 || env->best_score > (env->solut->score = (int)(((t_len + env->nb_ants - 1) / (env->solut->len)) + 0.999999f)))
        {
            env->best_score = env->solut->score;
            env->best_solut = env->solut;
            env->best_flow = flow_max;
        }
        env->solut = tmp;
    }
    else
    {
        env->solut = new_solut(env, extract_paths(env, &t_len), flow_max);
        env->solut->score = (int)(((t_len + env->nb_ants - 1) / (env->solut->len)) + 0.999999f);
        env->best_score = env->solut->score;
        env->best_solut = env->solut;
        env->best_flow = flow_max;
            // print_solut(env->solut);
    }
}