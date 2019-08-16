
#include "lem_in.h"

int     *int_set(int *tab, int val, int size)
{
    int     i;

    i = -1;
    while (++i < size)
        tab[i] = val;
    return (tab);
}

int     *int_concat(t_env *env, int *dest, int *src)
{
    int     i;
    int     j;

    i = 1;
    j = 0;
    while (i < env->flow_max)
        dest[i++] = src[j++];
    return (dest);
}

//a changer avec id_path qui donnes les calculs a faire pour quels chemins
int     count_score(t_env *env, int n_combo, int *id_paths)
{
    int     score;
    int     diff;
    int     i;

    i = 0;
    diff = 0;
    score = 0;
    while ((env->nb_ants + diff) % (n_combo + 1) != 0)
        diff++;
    while (i < n_combo)
    {
        score = ((env->nb_ants + diff) / n_combo) + path_len(env->paths[id_paths[i++]]) - 1 + score;
    }
    return (score / n_combo);
}

void    add_combo(t_env *env, int i, int j, int n_cv)
{
    env->combo[n_cv][0] = i;
    env->combo[n_cv][1] = j; 
}

void    add_tmp_combo(t_env *env, int i, int *paths, int n_cv)
{
    env->tmp_combo[n_cv][0] = i;
    env->tmp_combo[n_cv] = int_concat(env, env->tmp_combo[n_cv], paths);
}

int     icmp(t_env *env, int nb, int *tab)
{
    int     i;

    i = 0;
    while (i < env->nb_rooms && tab[i] != 1)
    {
        if (tab[i++] == nb)
            return (1);
    }
    return (0);
}

int     path_combo2(t_env *env, int *p_1, int *p_2)
{
    int     i;

    i = 1;
    while (i < env->nb_rooms && p_1[i] != 1)
    {
        if (icmp(env, p_1[i++], p_2))
            return (0);
    }
    return (1);
}

int     path_combo3(t_env *env, int *p_1, int *combo, int n_combo)
{
    int     i;
    int     j;

    i = 1;
    while (i < env->nb_rooms && p_1[i] != 1)
    {
        j = 0;
        while (j < (n_combo - 1))
            if (icmp(env, p_1[i], env->paths[combo[j++]]))
                return (0);
        i++;
    }
    return (1);
}

void cas_combo2(t_env *env, int n_combo, int i, int j)
{
    int     n_cv;

    n_cv = -1;
    while (++i < env->nb_valid)
    {
        j = i + 1;
        while (j < env->nb_valid)
        {
            if (n_cv + 1 < env->nb_valid && path_combo2(env, env->paths[i], env->paths[j]))
            {
                add_combo(env, i, j, ++n_cv);
                if (env->score > (env->tmp_score = count_score(env, n_combo, env->combo[n_cv])))
                {
                    // pstr(1, "meilleur score", '\n');
                    env->res = env->combo[n_cv];
                    env->score = env->tmp_score;
                }
            }
            j++;
        }
    }
}

void cas_combo3(t_env *env, int n_combo, int i, int j)
{
    int     n_cv;

    n_cv = -1;
    while (++i < env->nb_valid)
    {
        j = 0;
        while (j < env->nb_valid)
        {
            if (n_cv + 1 < env->nb_valid && env->combo[j][0] != -1 && path_combo3(env, env->paths[i], env->combo[j], n_combo))
            {
                add_tmp_combo(env, i, env->combo[j], ++n_cv);
                // print_path(env->tmp_combo[n_cv], env->flow_max);
                if (env->score > (env->tmp_score = count_score(env, n_combo, env->tmp_combo[n_cv])))
                {
                    // print_path(env->tmp_combo[n_cv], n_combo);
                    // pstr(1, "meilleur score", '\n');
                    env->res = env->tmp_combo[n_cv];
                    env->score = env->tmp_score;
                    // print_path(env->res, env->flow_max);
                }
            }
            j++;
        }
    }
}

void    replace_tmp_combo(t_env *env)
{
    int     i;

    i = -1;
    while (++i < env->nb_valid)
    {
        memcp(env->combo[i], env->tmp_combo[i], sizeof(int) * env->flow_max);
        int_set(env->tmp_combo[i], -1, env->flow_max);
    }
}

void    combo_optimal(t_env *env)
{
    int n_combo;

    n_combo = 1;
    // env->res[0] = 0;
    env->score = count_score(env, n_combo, 0);
    env->combo = alloc_matrix_int(env->flow_max, env->nb_valid, -1);//nombre de combo a revoir
    env->tmp_combo = alloc_matrix_int(env->flow_max, env->nb_valid, -1);
    while (++n_combo <= env->flow_max)
    {
        if (n_combo == 2)
            cas_combo2(env, n_combo, -1, 0);
        else
        {
            // print_tab(env->combo, env->flow_max, env->nb_valid);
            cas_combo3(env, n_combo, -1, 0);
            // print_tab(env->tmp_combo, env->flow_max, env->nb_valid);
            // pstr(1, "teste", '\n');
            replace_tmp_combo(env);
        }
    }
    free_matrix(&env->combo, env->nb_valid);
    free_matrix(&env->tmp_combo, env->nb_valid);
    // print_tab(env->combo, env->flow_max, env->nb_valid);
    print_path(env->res, env->flow_max);
}