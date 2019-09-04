/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ek.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:20:25 by plaurent          #+#    #+#             */
/*   Updated: 2019/08/01 17:48:37 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    open_upstream(t_env *env, int **tmp_matrix, int blocked_room)
{
    int i;
    int j;

    i = blocked_room; 
    j = 0;
    while (j < (int)env->nb_rooms && i > 0)
    {
        if (tmp_matrix[i][j] >= 2 && i != j && tmp_matrix[i][i] <= tmp_matrix[i][j])
        {
                tmp_matrix[i][j] = 1;
                tmp_matrix[j][i] = 1;
                if (tmp_matrix[i][i] >= 2)
                    tmp_matrix[i][i] = 0;
            i = j;
            j = 0;
        }
        else
            j++;
    }
}

void    open_downstream(t_env *env, int **tmp_matrix, int blocked_room)
{
    int i;
    int j;

    i = blocked_room; 
    j = 0;
    while (j < (int)env->nb_rooms && i > 0)
    {
        if (tmp_matrix[i][j] >= 2 && i != j && tmp_matrix[i][i] >= tmp_matrix[i][j])
        {
            if (i != blocked_room)
            {
                tmp_matrix[i][j] = 1;
                tmp_matrix[j][i] = 1;
                if (tmp_matrix[i][i] >= 2)
                    tmp_matrix[i][i] = 0;
            }
            i = j;
            j = 0;
        }
        else
            j++;
    }
}

// int     is_shorter(int *first_path, int *new_path)
// {
//     int i;
//     int first_size;
//     int new_size;

//     i = 1;
//     new_size = 0;
//     while (i > 0)//on compte la taille de new_path
//     {
//         if (new_path[i] >= 0)
//             i = new_path[i];
//         else
//             break;
//         new_size++;
//     }
//     i = 1;
//     first_size = 0;
//     while (i > 0 && first_path[1] != -1)//on compte la taille de first_path
//     {
//         if (first_path[i] >= 0)
//             i = first_path[i];
//         else
//             break;
//         first_size++;
//     }
//     if (new_size < first_size)//si new_path < first_path
//         return (1);
//     return (0);
// }

/*
update matrix sert a modifier la matrix en fonction de new_path
pour enregistrer le chemins dans la matrix
*/
static void update_matrix(t_env *env, int *new_path, int id)
{
    int     room;
    int     i;
    int     k;

    room = 1;
    i = -1;
    k = 0;
    id = 0;
    // env->links[new_path[i]][new_path[i]] = id + 2;
    // env->links[new_path[i]][new_path[i + 1]] = 2 + k;
    // env->links[new_path[i + 1]][new_path[i]] = 2 + k;
    while (new_path[++i] != -1 && new_path[i] != 1)
    {
        // ft_printf("%s|", env->rooms[room].name); // TEST
        if (i > 0)
            env->links[new_path[i]][new_path[i]] = i + 1;
        env->links[new_path[i]][new_path[i + 1]] = 2 + k;
        env->links[new_path[i + 1]][new_path[i]] = 2 + k;
        k++;
    }
    // ft_printf("%s\n", env->rooms[room].name); // TEST
}

/*
char    *sp_join_res(char *all_res, int *res)
{
    char    *str;
    int     j;
    int     i;
    int     size;

    i = 1;
    j = 0;
    size = get_path_size(res);
    if (!(str = malloc(sizeof(char) * size + 1)))
        return (NULL);
    while(i > 0)
    {
        str[j] = i + '0';
        i = res[i];
        j++;
    }
    str[j] = '\n';
    if (!all_res)
        return (str);
    else
        return (all_res = ft_strjoin(all_res, str));
}*/

// void    add_paths(t_path *all_paths, int *new_path, int flow)
// {
//     int i;

//     i = 0;
//     while (i < flow - 1)
//     {
//         all_paths[flow].paths[i] = all_paths[flow - 1].paths[i];  
//         i++;
//     }
//     all_paths[flow].paths[flow - 1] = new_path;
// }

// int     find_other_paths(t_data *data, t_path *all_paths, int flow) // EV : C'est sur qu'il faut reboucler sur check blocking ou faire autrement
// {
//     int     i;
//     int     *new_path;

//     i = 0;
//     while (i < flow) // en gros si on a blocage et qu'on trouve une soluce il faut trouver le ou les autres chemins qui marchent avec cette alternative
//     {                //faudra peut etre rajouter des conditions si le nouveau chemin ne cree pas d'autres blocage et donc peut etre recommencer avec check blocking
//                      //et on est sur que ca ne tournera pas en boucle car un blocage ne peut pas etre tester 2x mais a faire attention que ce ne soit pas trop long comme ce commentaire
//         if (!(new_path = bfs(data, data->matrix)))
//             return (0);
//         if (new_path[1] != -1)
//         {
//             ft_putstr("New path in find other path : \n");
//             print_one_path(new_path);
//             update_matrix(data, new_path);
//             all_paths[flow].paths[i + 1] = new_path; // EV : On ajoute un chemin, i + 1 car la case [0] est prise depuis la fonction blocking 
//             //all_res = sp_join_res(all_res, new_path);
//             //path = newpath(path, new_path, flow); //a verif si il ya un cas ou en deblocant on trouve une alternative au premier chemin mais qu'on trouve tjrs pas de deuxieme chemins
//         }
//         else //EV : ici pour le rebouclage check blocking ?
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int     *check_blocking(t_data *data, int *first_path)
// {
//     int i;
//     int *new_path;
//     int **tmp_matrix;

//     while (1) // tant que tout les blocages n'ont pas ete traités
//     {
//         tmp_matrix = ft_matrixdup(data->matrix, data->nb_rooms);
//         i = 0;
//         while (i < (int)data->nb_rooms && data->block[i] <= 0) //on cherche un blocage et si il n'y en a pas on sort de check blocking
//             i++;
//         if (i == (int)data->nb_rooms) // EV : useless ?
//             return (first_path);
//         open_upstream(data, tmp_matrix, i);
//         if (!(new_path = bfs(data, tmp_matrix))) //teste en ayant debloquer
//             return (NULL);
//         if (new_path[1] != -1)//TEST
//         {
//             ft_putstr("New path in check_blocking : \n");//TEST
//             print_one_path(new_path);//TEST
//         }
//         if ((new_path[1] != -1 && is_shorter(first_path, new_path)) || (first_path[1] == -1 && new_path[1] != -1)) // soit le nouveau chemin est plus rapide
//         {
//             open_downstream(data, tmp_matrix, i);
//             data->matrix = tmp_matrix;
//             first_path = new_path;
//         }
//         data->block[i] = -1; //supprime blocage et le met en "deja check" d'ou le -1
//     }
//     return (first_path); // EV : et pas return (new_path); ???
// }

// int     blocking(t_data *data, int *first_path, t_path *all_paths, int flow)
// {//important, dans check blocking si on a trouver des nouveau chemins mais avant il y avait eu d'autre chemins il faut peut etre comparer leur deux score ou alors c est inutile ?
//     //char    *tmp_all_res = NULL;
//     int     *new_path;

//     new_path = check_blocking(data, first_path);
//     if (new_path[1] != -1)
//     {
//         ft_putstr("New path in blocking : \n");
//         print_one_path(new_path);
//         //tmp_all_res = sp_join_res(tmp_all_res, new_path); // STOP DEV ACTUEL
//         update_matrix(data, new_path);
//         all_paths[flow].paths[0] = new_path; // EV : On ajoute un chemin // Faire peut etre une fonction pour mettre a la premiere place dispo

//         if (new_path == first_path) // EV : voir ca dans check_blocking // Pas sur // a mettre au debut de la fonction ?
//             add_paths(all_paths, new_path, flow); //Pas sur
//         else if (find_other_paths(data, all_paths, flow))
//             return (1);
//         return (1);
//         //else
//         //    return (all_path);
//     }
//     else
//         ft_printf("CHECK BLOCKING N'A TROUVE AUCUNE SOLUTION !!!\n");//TEST
//     return (0);
// }

// t_path     *init_all_paths(int flow_max) // Rajouter une initialisation a NULL ?
// {
//     t_path      *all_paths;
//     int         i;

//     i = 1;
//     if (!(all_paths = (t_path*)malloc(sizeof(t_path) * flow_max + 1)))
//         return (NULL);
//     while (i <= flow_max)
//     {
//         if (!(all_paths[i].paths = (int**)malloc(sizeof(int*) * i)))
//             return (NULL);
//         i++;
//     }
//     return (all_paths);
// }

int		*ft_intrev(int *tab, size_t size)
{
	int     temp;
    size_t  i;

    i = 0;
    while (i < (size / 2))
    {   
        temp = tab[i];
        tab[i] = tab[size - 1 - i];
        tab[size - 1 - i] = temp;
        i++;
    }
    return (tab);
}

int	 ffy(int **paths, int y_start, int size_y)
{
	int i = y_start - 1;

	while (++i < size_y - 1) {
		if (paths[i][1] == -1) {
			return i;
		}
	}
	return -1;
}

void        add_path(t_env *env, int *path, int flow)
{
    int     i;
    int     j;
    int     *tmp_path = NULL;
    int     id_path;

    i = 1;
    j = 0;
    flow = 0;
    if (path[i] == -1)
        return ;
    // ft_printf("teste\n");
    tmp_path = int_set(tmp_path, -1, env->nb_rooms);
    tmp_path[j++] = 1;
    while (i != 0)
    {
        tmp_path[j] = path[i];
        i = path[i];
        j++;
    }
    tmp_path = ft_intrev(tmp_path, j);
    id_path = ffy(env->paths, 0, env->nb_paths);
    print_array_int(tmp_path, env->nb_rooms);
    ft_memcpy(env->paths[id_path], tmp_path, sizeof(int) * env->nb_rooms);
    update_matrix(env, tmp_path, id_path);
    free(tmp_path);
    // env->nb_valid++;
}

// int         good_block(t_env *env, int block, int *first_path, int len_max)
// {
// //if ("la taille jusqua first block + la taille de first block a end" > "la taille du chemins 1 plus celle de path fbfs")
//         //bloquage non utilisable
//     int     len_until_end;
//     int     len_before_block;

//     len_until_end = len_until(env, block, 1);
//     len_before_block = len_before(env, block);
//     if ((len_until_end + len_before_block) >= len_max)
//         return (0);
//     return (1);
// }

// void        add_unblocking_path(t_env *env, int *path_fbfs, int block)
// {
//     int     *tmp_path;
//     int     i;
//     int     j;
//     int     k;
//     int     id_path;

//     tmp_path = NULL;
//     tmp_path = int_set(tmp_path, -1, env->nb_rooms);
//     i = env->block[block];
//     j = -1;
//     // while (++j < env->nb_rooms)
//     //         ft_printf("case n:%d, %d |", j,  path_fbfs[j]);
//     // j = 0;
//     // while (++j < env->nb_rooms)
//     //         ft_printf("case n:%d, %d |", j,  env->block[j]);
//             j = 0;
//     ft_printf("teste\n");
//     while (i != 0)
//     {
//         ft_putnbr(tmp_path[j++] = i);
//         i = path_fbfs[i];
//     }
//     tmp_path[j++] = 0;
//     tmp_path = ft_intrev(tmp_path, j);
//     tmp_path[j++] = block;
//     i = block;
//     while (i != 1)
//     {
//         k = 0;
//         while (i != k && env->links[i][k] <= 1)
//             k++;
//         tmp_path[j++] = k;
//         i = k;
//     }
//     id_path = ffy(env->paths, 0, env->nb_paths);
//     print_array_int(tmp_path, env->nb_rooms);
//        ft_printf("teste\n");
//     ft_memcpy(env->paths[id_path], tmp_path, sizeof(int) * env->nb_rooms);
//     update_matrix(env, tmp_path, id_path);
//     free(tmp_path);
//        ft_printf("teste\n");
//     // env->nb_valid++;
// }

int        blockage(t_env *env, int *path_fbfs, int first_block, int flow)
{
    int     **tmp_matrix;
    int     *tmp_path;
    int     max_len;
    int     i;

    max_len = 0;
    i = 0;
    if (path_fbfs[1] != -1)
        while (i != 0)
        {
            ft_printf("teste");
            i = path_fbfs[i];
            max_len++;
        }
    // while (1)
    // {
        while (first_block > 0 && env->block[first_block] <= 0) // la on a le dernier bloquage
            first_block--;
        // ft_putnbr(env->links[first_block][first_block]); la taille depuis start
        // if (first_block == 0)
        //     return (NULL);
        // if (!good_block(env, first_block, path_fbfs, max_len))
        //     return (NULL);
        // if (!tmp_matrix)
        tmp_matrix = ft_matrixdup(env->links, env->nb_rooms);
        // print_matrix_int(tmp_matrix, env->nb_rooms, env->nb_rooms);
        open_downstream(env, tmp_matrix, first_block);
        // ft_putchar('\n');
        // print_matrix_int(tmp_matrix, env->nb_rooms, env->nb_rooms);
        if ((tmp_path = bfs(env, tmp_matrix, 0)) && tmp_path[1] != -1) // il faut le bfs s'arrete quand il a depasser la taille jusqu'a laquele le bloquage est utile
        {
            // ft_printf("teste");
            // print_array_int(tmp_path, env->nb_rooms);
            open_upstream(env, tmp_matrix, first_block);
                    // print_matrix_int(tmp_matrix, env->nb_rooms, env->nb_rooms);
            env->links = tmp_matrix;
            add_path(env, tmp_path, flow);
            tmp_path = bfs(env, env->links, 0);
            add_path(env, tmp_path, flow);
            env->block[first_block] = -1;
            // if (path_fbfs[1] != -1)
            // add_unblocking_path(env, path_fbfs, first_block);
            // else
            //     add_path(env, bfs(env, env->links, 0), flow);
            return (1);
        }
    // }
    free_matrix((void**)tmp_matrix, env->nb_rooms);
    return (0);
}

int         sp_path_len(t_env *env, int *path)
{
    int     i;
    int     len;

    len = 0;
    i = 1;
    while (i < env->nb_rooms && i != 0)
    {
        i = path[i];
        len++;
    }
    return (len); 
}

void        ek(t_env *env)  // RES EST MTN NEW_PATH
{
    int         flow;
    int         *new_path;
    int         i;
    // int         **paths;

    flow = 1;
    i = 0;
    (env->paths = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_paths, -1)) ?
	0 : perr(env, "Error: tmp_paths malloc failed");
    // if (!(all_paths = init_all_paths(env->flow_max)))
    //     return (NULL);
    while (flow <= env->flow_max)
    {
        // print_matrix_int(env->links, env->nb_rooms, env->nb_rooms);
        if (!(new_path = bfs(env, env->links, 1)))
            return ;
        while (i < env->nb_rooms && env->block[i] != 0)
            i++;
        // if (sp_path_len(env, new_path) > 100 && flow > 15)
        //     break ;
        ft_printf("\n i: %d\n", i);
        if (new_path[1] >= 0 && i == env->nb_rooms)//cas de non blocage
        {
            // ft_printf("EK : Cas de chemin libre pour flow(%d)\n", flow);//TEST
            add_path(env, new_path, 0);
            // env->nb_valid++;
        }
        else if (flow <= (int)15)//cas de blocage
        {
            ft_printf("EK : Cas de blocage pour flow(%d)\n", flow);//TEST
            if (blockage(env, new_path, env->nb_rooms - 1, flow) == 0)
                break ;
            // env->block = NULL;
            // free(env->block);
            // env->nb_valid--;
            // print_array_int(env->block, env->nb_rooms);
            // return ;
            /*
            **  dans bloquage on calcule dabord len des chemins deja present avec celui hors blockage si y a
            **  sinon on met a -1 ensuite avant un bloquage on regarde si le fbfs est
            **  moins bien que celui que donnerais le bloquage.
            */
            // ft_putstr("New path before blocking : \n");//TEST
            // print_one_path(new_path);//TEST
            // if (!blocking(data, new_path, all_paths, flow))// flow a ete modifie (+1)
            //     return (NULL);
        }
        else
            break ;
        
        free(new_path);
        flow++;
    }
    i = 0;
    while (i < env->nb_paths && env->paths[i++][0] == 0)
        env->nb_valid++;
    ft_putnbr(env->nb_valid);
    //data->flow_max = flow - 1;
}
