
#include "lem_in.h"
//a changer avec id_path qui donnes les calculs a faire pour quels chemins
int     count_score(t_env *env, int n_combo, int *id_paths)
{
    int     score;
    int     diff;
    int     i;

    i = 0;
    diff = 0;
    while ((env->nb_ants + diff) % (n_combo + 1) != 0)
        diff++;
    while (i < n_combo)
        score = ((env->nb_ants + diff) / n_combo) + path_len(env->paths[id_paths[i++]]) - 1 + score;
    return (score);
}

void    add_combo(t_env *env, int i, int j, int n_cv)
{
    env->combo[n_cv][0] = i + '0';
    env->combo[n_cv][1] = j + '0'; 
}

void    add_tmp_combo(t_env *env, int i, char *paths, int n_cv)
{
    env->tmp_combo[n_cv][0] = i + '0';
    env->tmp_combo[n_cv] = ft_strcat(env->tmp_combo, paths, '\0');
}

void cas_combo2()
{
    while (++i < env->nb_valid)
    {
        j = i + 1;
        while (j < env->nb_valid)
        {
            if (n_combo == 2 && i != j && path_combo(env->paths[i], env->paths[j]))
            {
                add_combo(env, i, j, ++n_cv);
                if (env->score < (env->tmp_score = count_score(env, n_combo, env->combo[n_cv])))
                {
                    env->res = memcp(env->res, env->combo[n_cv], n_combo);
                    env->score = env->tmp_score;
                }
            }
        }
    }
}

void cas_combo3()
{
    while (++i < env->nb_valid)
    {
        j = i + 1;
        while (j < env->nb_valid)
        {
            if (n_combo > 2 && path_combo(env->paths[i], env->combo[j]))
            {
                add_tmp_combo(env, i, env->combo[j], ++n_cv);
                if (env->score < (env->tmp_score = count_score(env, n_combo, env->tmp_combo[n_cv])))
                {
                    env->res = memcp(env->res, env->tmp_combo[n_cv], n_combo);
                    env->score = env->tmp_score;
                }
            }
        }
    }
}

void combo_optimal(t_env *env)
{
    int n_combo;
    int i;
    int j;
    int n_cv;

    i = -1;
    n_combo = 1;
    if (!(env->res = (char *)malloc(sizeof(char) * env->flow_max)))
        ;
    return;
    env->res = mems(env->res, -1, env->flow_max);
    env->res[0] = '0';
    env->score = count_score(env, n_combo, env->res[0]);
    env->combo = alloc_matrix_char(env->flow_max, env->nb_valid - 1);
    env->tmp_combo = alloc_matrix_char(env->flow_max, env->nb_valid - 1);
    while (++n_combo < env->flow_max)
    {
        n_cv = -1;
        cas_combo2());
        // while (++i < env->nb_valid)
        // {
        //     j = i + 1;
        //     while (j < env->nb_valid)
        //     {
        //         // if (n_combo == 2 && i != j && path_combo(env->paths[i], env->paths[j]))
        //         // {
        //         //     add_combo(env, i, j, ++n_cv);
        //         //     if (env->score < (env->tmp_score = count_score(env, n_combo, env->combo[n_cv])))
        //         //     {
        //         //         env->res = memcp(env->res, env->combo[n_cv], n_combo);
        //         //         env->score = env->tmp_score;
        //         //     }
        //         // }
        //         // else if (n_combo > 2 && path_combo(env->paths[i], env->combo[j]))
        //         // {
        //         //     add_tmp_combo(env, i, env->combo[j], ++n_cv);
        //         //     if (env->score < (env->tmp_score = count_score(env, n_combo, env->tmp_combo[n_cv])))
        //         //     {
        //         //         env->res = memcp(env->res, env->tmp_combo[n_cv], n_combo);
        //         //         env->score = env->tmp_score;
        //         //     }
        //         // }
        //     }
        // }
    }
}