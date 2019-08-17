
#include "lem_in.h"
#include <stdio.h>

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
int     count_score(t_env *env, int n_combo, int *combo)
{
    int     score;
    int     diff;
    int     i;

    i = -1;
    diff = 0;
    score = 0;
    n_combo < 1 ? n_combo = 1 : 0;
    while ((env->nb_ants + diff) % (n_combo + 1) != 0)
        diff++;
    while (++i < n_combo)
        score += ((env->nb_ants + diff) / n_combo)
        + path_len(env->paths[combo[i]], env->nb_rooms) - 1;
    return (score / n_combo);
}

int     paths_compatible(int *p1, int *p2, int size)
{
    int i;
    int j;

    i = 0;
    while (++i < size && p1[i] != 1 && p1[i] != -1 && (j = -1))
        while (++j < size && p2[j] != 1 && p2[j] != -1)
            if (p1[i] == p2[j])
                return (0);
    return (1);
}

int     combo_x_compatible(t_env *env, int *path, int *combo_2, int n_combo)
{
    int     i;

    i = -1;
    while (++i < n_combo && combo_2[i] != -1)
        if (!paths_compatible(path, env->paths[combo_2[i]], env->nb_rooms))
            return (0);
    return (1);
}

void    get_combo_2(t_env *env, int **combo_2, int n_combo)
{
    int     n_cv;
    int     score;
    int     i;
    int     j;

    i = -1;
    n_cv = -1;
    while (++i < env->nb_valid && (j = i) >= 0)
        while (++j < env->nb_valid)
            if (paths_compatible(env->paths[i], env->paths[j], env->nb_rooms))
            {
            //    pstr(1, "is compatible", '\n'); 
                combo_2[++n_cv][0] = i;
                combo_2[n_cv][1] = j;
                if (env->best_score > (score = count_score(env, n_combo, combo_2[n_cv])))
                {
                    pstr(1, "meilleur score 2", '\n');
                    memcp(env->best_combo, combo_2[n_cv], env->flow_max * sizeof(int));
                    env->best_score = score;
                    env->best_flow = n_combo;
                }
            }
    // print_matrix_int(combo_2, env->flow_max, env->nb_valid);
}

void get_combo_x(t_env *env, int **combo_2, int **combo_x, int n_combo)
{
    int     n_cv;
    int     score;
    int     i;
    int     j;

    i = -1;
    n_cv = -1;
    while (++i < env->nb_valid && (j = -1))
        while (++j < env->nb_valid)
            if ((n_cv + 1) < env->nb_valid && combo_2[j][0] != -1 && combo_x_compatible(env, env->paths[i], combo_2[j], n_combo))
            {
                combo_x[++n_cv][0] = i;
                int_concat(env, combo_x[n_cv], combo_2[j]);
                // memcp(&combo_x[n_cv], combo_2[j], sizeof(int) * env->flow_max);
                // print_array_int(combo_x[n_cv], env->flow_max);
                if (env->best_score > (score = count_score(env, n_combo, combo_x[n_cv])))
                {
                    // print_array_int(env->combo_x[n_cv], n_combo);
                    // pstr(1, "meilleur score X", '\n');
                    memcp(env->best_combo, combo_x[n_cv], env->flow_max * sizeof(int));
                    env->best_score = score;
                    env->best_flow = n_combo;
                    // print_array_int(env->best_combo, env->flow_max);
                }
            }
}

void    replace_combo_x(t_env *env, int **combo_2, int **combo_x)
{
    int     i;

    i = -1;
    while (++i < env->nb_valid)
    {
        memcp(combo_2[i], combo_x[i], sizeof(int) * env->flow_max);
        int_set(combo_x[i], -1, env->flow_max);
    }
}

void    combo_optimal(t_env *env)
{
    int n_combo;
    int **combo_2;
    int **combo_x;

    if (env->nb_valid > 0)
    {
        ((env->best_combo = alloc_array_int(env->flow_max, -1))
        && (combo_2 = alloc_matrix_int(env->flow_max, env->nb_valid, -1))
        && (combo_x = alloc_matrix_int(env->flow_max, env->nb_valid, -1)))
        ? 0 : put_error(env, "Error: one of combo malloc failed");
        n_combo = 2;
        env->best_combo[0] = 0;
        env->best_score = count_score(env, 1, env->best_combo);
        get_combo_2(env, combo_2, n_combo);
        while (++n_combo <= env->flow_max)
        {
            // print_matrix_int(env->combo_2, env->flow_max, env->nb_valid);
            get_combo_x(env, combo_2, combo_x, n_combo);
            // print_matrix_int(combo_x, env->flow_max, env->nb_valid);
            // pstr(1, "teste", '\n');
            replace_combo_x(env, combo_2, combo_x);
        }
        print_array_int(env->best_combo, env->flow_max);
        // print_matrix_int(combo_2, env->flow_max, env->nb_valid);
        free_matrix_int(&combo_2, env->nb_valid);
        free_matrix_int(&combo_x, env->nb_valid);
    }
    else {
        put_error(env, "No combo found as env->nb_valid = 0\n");
    }
}
