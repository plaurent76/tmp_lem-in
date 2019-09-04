/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:57:06 by eviana            #+#    #+#             */
/*   Updated: 2019/08/01 17:22:11 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     *sp_int_set(int *tab, int val, int size)
{
    int     i;

    i = -1;
    if (!tab)
        if (!(tab = (int*)malloc(sizeof(int) * size)))
            return (0);
    while (++i < size)
        if (tab[i] != -1)
            tab[i] = val;
    return (tab);
}

int     **ft_matrixdup(int **src, size_t size) // A rajouter dans libft si bien faite
{
        int             **matrix;
        int     i;
    int     j;

    i = 0;
    if (!(matrix = (int**)malloc(sizeof(int*) * size)))
        return (NULL);
    while (i < (int)size)
    {
        j = 0;
        if (!(matrix[i] = (int*)malloc(sizeof(int) * size)))
            return (NULL);
        while (j < (int)size)
        {
            matrix[i][j] = src[i][j];
            j++;
        }
        i++;
    }
    return (matrix);
}

void    next_queue(t_env *env, int *queue) // Peut etre optimise avec la variable j de bfs
{
    int  i;

    i = 0;
    while (i + 1 < env->nb_rooms)
    {
        queue[i] = queue[i + 1];
        i++;
    }
}

int       *bfs(t_env *env, int **matrix, int b) // le param "res" peut etre retire
{
    int         **tmp_matrix = NULL;
    int         *queue = NULL;
    int         *path = NULL;
    int         i;
    int         j;

    ft_printf("        --- BFS ---        \n");//TEST
    if (!(path = int_set(path, -1, env->nb_rooms)))
        return (NULL);
    if (!(tmp_matrix = ft_matrixdup(matrix, env->nb_rooms)))
        return (NULL);
    if (!(env->block = sp_int_set(env->block, 0, env->nb_rooms)))
        return (NULL);
    if (!(queue = int_set(queue, -1, env->nb_rooms)))
        return (NULL);
    queue[0] = 0;
    while (queue[0] != 1 && queue[0] != -1)
    {
        i = 0;
        while (i < (int)env->nb_rooms)
        {
            if (i != queue[0] && tmp_matrix[queue[0]][i] == 1 && tmp_matrix[i][i] == 0) // EV : si la salle en premiere position dans la queue est en lien avec la salle i qu'on passe en revue
            {
                j = 0;
                while (queue[j] != -1)
                    j++;
                queue[j] = i;
                tmp_matrix[i][i] = 1; // on note qu'on a passe la salle i en revue
                if (path[i] == -1)
                path[i] = queue[0];
            }
            else if (b == 1 && i != queue[0] && tmp_matrix[queue[0]][i] == 1
            && tmp_matrix[i][i] >= 2 && queue[0] > 0 && env->block[i] == 0) // cas ou bloquage par une room deja empruntée
            {
                ft_printf("bloquage room: %d et i: %d", queue[0], i);
                env->block[i] = queue[0];
            }
            i++;
        }
        next_queue(env, queue); //suppression de la room qu'on vient de regarder et on swap pour que queue[0] soit la prochaine room a regarder
    }
    return (path);
}

int       *bfs_until(t_env *env, int **matrix) // le param "res" peut etre retire
{
    int         **tmp_matrix = NULL;
    int         *queue = NULL;
    int         *path = NULL;
    int         i;
    int         j;

    ft_printf("        --- BFS UNTIL ---        \n");//TEST
    if (!(path = int_set(path, -1, env->nb_rooms)))
        return (NULL);
    if (!(tmp_matrix = ft_matrixdup(matrix, env->nb_rooms)))
        return (NULL);
    // if (!(env->block = sp_int_set(env->block, 0, env->nb_rooms)))
    //     return (NULL);
    if (!(queue = int_set(queue, -1, env->nb_rooms)))
        return (NULL);
    queue[0] = 0;
    while (queue[0] != 1 && queue[0] != -1)
    {
        i = 0;
        while (i < (int)env->nb_rooms)
        {
            if (i != queue[0] && tmp_matrix[queue[0]][i] == 1 && tmp_matrix[i][i] == 0)
            {
                j = 0;
                while (queue[j] != -1)
                    j++;
                queue[j] = i;
                tmp_matrix[i][i] = 1; // on note qu'on a passe la salle i en revue
                if (path[i] == -1)
                path[i] = queue[0];
            }
            else if (i != queue[0] && tmp_matrix[queue[0]][i] == 1 && tmp_matrix[i][i] >= 2 && queue[0] > 0) // && env->block[i] == 0) // cas ou bloquage par une room deja empruntée
            {
                path[i] = queue[0];
                // i = queue[0];
                // j = 0;
                while (1)
                {
                    j = 0;
                    while (j < env->nb_rooms && i != j && tmp_matrix[i][j] <= 2 && tmp_matrix[i][j] < tmp_matrix[j][j]) // je recule
                        j++;
                    if (j != 0 && j < env->nb_rooms)
                    {
                        path[j] = i;
                        i = 0;
                        while (i < env->nb_rooms && i != j && tmp_matrix[i][j] == 1 && tmp_matrix[i][i] == 0) // je regarde si ona une sortie
                            i++;
                        if (i < env->nb_rooms)
                        {
                            path[i] = j;
                            j = 0;
                            while (queue[j] != -1)
                                j++;
                            queue[j] = i;
                            tmp_matrix[i][i] = 1;
                            break;
                        }
                        else
                        {
                            path[j] = i;
                            i = j;
                        }
                    }
                    else
                        break;
                }
                // recule jusqu'a trouver une sortie
                // path[i] = queue[0];
                // on doit forcement reculer et non avancer dans le chemin qui nous bloque 
                // en pour cela sufit de regarder si le pipe est plus petit/grand que la room
                // env->block[i] = queue[0];
            }
            i++;
        }
        next_queue(env, queue); //suppression de la room qu'on vient de regarder et on swap pour que queue[0] soit la prochaine room a regarder
    }
    return (path);
}