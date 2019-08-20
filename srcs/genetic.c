/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genetic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:25:39 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:25:40 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	 ffy(int **paths, int y_start, int size_y)
{
	int i = y_start - 1;

	while (++i < size_y) {
		if (paths[i][1] == -1) {
			return i;
		}
	}
	return -1;
}

int	 ffx(int **paths, int y, int size_x)
{
	int i = -1;

	while (++i < size_x) {
		if (paths[y][i] == -1) {
			return i;
		}
	}
	return 0;
}

// first valid from
int 	fvf(int **paths, int from, int size_x, int size_y)
{
	int i;
	int j;

	j = from;
	while (j++ < size_y)
	{
		i = -1;
		while (++i < size_x)
			if (paths[j][i] == 1)
				return j;
	}
	return -1;
}

int		ending_path(int **paths, int y, int size_y)
{
	int		i;

	i = -1;
	while (i < size_y && paths[y][++i] != -1)
	{
		if (paths[y][i] == 1 || i + 1 == size_y)
			return (1);
	}
	return (0);
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path_until(int **paths, int until, int size_y, int y_src)
{
	int 	y;
	// int		*tmp;
	// tmp = NULL;
	y = ffy(paths, y_src, size_y);
	if (y == -1)
		return -1;
	// 
	// else
		memcp(paths[y], paths[y_src], (until) * sizeof(int));
	// printf("duplicated: %d >> %d\n", y_src, y);
	return (y);
}

int 	paths_match(int *path1, int *path2, int length)
{
	int 	i;

	i = -1;
	while (++i < length)
		if (path1[i] != path2[i])
			return (0);
	return (1);
}

// checks if room is already in path and if path is not duplicate from last one
int		room_used(int **paths, int path_n, int until, int id)
{
	int 	length;

	length = -1;
	while (++length < until && paths[path_n][length] != -1)
	{
		if (paths[path_n][length] == id)
		{
			// printf("room %d found in path %d at length %d: ", id, path_n, length);
			// print_array_int(paths[path_n], length + 1);
			return (1);
		}
	}
	// length = length < until ? length : until;
	// printf("room %d NOT found in path %d of length %d: ", id, path_n, length);
	// print_array_int(paths[path_n], length);
	if (path_n > 0) {
		//printf("path_n: %d length: %d\n", path_n, length);
		if (paths_match(paths[path_n], paths[path_n - 1], length)
			&& (id == paths[path_n - 1][length])) {
			return (1);
		}
		//bullshit
		// printf("comparing previous path:\n");
		// print_array_int(paths[path_n-1], length);
		// printf("with new path:\n");
		// print_array_int(paths[path_n], length);
		// printf("path_match:%s\n", paths_match(paths[path_n], paths[path_n - 1], length) ? "yes\n" : "no\n");

		// printf("comparing last room of previous with new room to add:\n");
		// printf("%d vs %d match:%s\n", id, paths[path_n - 1][length], (id == paths[path_n - 1][length]) ? "yes\n" : "no\n");
		// //end of bullshit

	}
	
	return (0);
}

void	del_path(int **paths, int path_n)
{
	int 	i;

	i = -1;
	while (paths[path_n][++i] > -1)
		paths[path_n][i] = -1;
}

void	add_to_path(int **paths, int size_x, int y, int room_id)
{
	paths[y][ffx(paths, y, size_x)] = room_id;
}

int 	clean_paths(int **paths, int start_y, int size_y, int size_x)
{
	int		i;
	int		cnt;
	int		to_clean;
	int		y;
	// int		last_full;

	i = start_y - 1;
	y = start_y;
	cnt = 0;
	// print_matrix_int(paths, size_x, size_y);
	while (++i < size_y && paths[i][0] != -1)
		if (!ending_path(paths, i, size_x) && ++cnt)
			int_set(paths[i], -1, size_x);
	// cnt = (size_y - start_y) - cnt;
	to_clean = cnt;
	// last_full = i;
	while (--cnt >= 0)
	{
		while (i > 0 && paths[i][0] == -1)
			--i;
		y = ffy(paths, y, size_y);
		if (y >= (i))
			break;
		memcp(paths[y], paths[i], (size_x) * sizeof(int));
		int_set(paths[i], -1, size_x);
	}
	// print_matrix_int(paths, size_x, size_y);
	// if (IS_SET_V)
		// printf("tmp_paths cleaned: from=%d to=%d sum=%d\n", start_y, last_full, to_clean);
	return (to_clean);
}

int		use_node(t_env *env, int room_id)
{
	int i = -1;

	while (++i < env->flow_start_max)
		if (env->node_exploration[i][0] == room_id)
			if (env->node_exploration[i][1]++)
				return (1);
	return (0);
}

int		is_node_explored(t_env *env, int room_id)
{
	int i = -1;

	while (++i < env->flow_start_max)
		if (env->node_exploration[i][0] == room_id)
			if (env->node_exploration[i][1] >= env->max_paths_per_node)
				return (1);// tu devrais pas test ici si on est passer
				//1024x sur un noeud de start ? 
	return (0);
}

void 	explore_paths(t_env *env, int **paths, int path_n, int room_id)
{
	int 	n_link;
	int 	path_n_duplicate;
	int		path_n_length;
	int		x;

	x = -1;
	n_link = 0;
	if (!path_n && paths[0][0] == -1)
	{
		path_n = ffy(paths, path_n, env->nb_paths);
		if (path_n == -1)
			return ;
		add_to_path(paths, env->nb_rooms, path_n, room_id);
	}
	if (is_node_explored(env, paths[path_n][1]))
		return ;
	use_node(env, paths[path_n][1]);
	// printf("just explored by node (room_id): %d\n", paths[path_n][1]);
	// print_matrix_int(env->node_exploration, 2, env->flow_start_max);

	path_n_duplicate = path_n;
	path_n_length = 0;
	while (path_n_length < env->nb_rooms && paths[path_n][path_n_length] != -1)
		path_n_length++;
	while (++x < (int)env->nb_rooms)
	{
		// checks if room is already in path and if path is not duplicate from last one
		if (env->links[room_id][x] && !room_used(paths, path_n, env->nb_rooms, x) && ++n_link) // link exists with start
		{
			if (n_link > 1)
			{
				if (path_n_duplicate > 0 && room_id == 0)
				{ // we found at least 1 path starting from 0
					clean_paths(paths, 0, env->nb_paths, env->nb_rooms);
				}
				path_n_duplicate = duplicate_path_until(paths, path_n_length, env->nb_paths, path_n);
			}
			if (path_n_duplicate == -1)
				return ;
			add_to_path(paths, env->nb_rooms, path_n_duplicate, x);
			// print_matrix_int(tmp_paths, env->nb_rooms, env->nb_paths);
			// printf("explore path %d from room %d\n", path_n, x);
			if (x != 1)
				explore_paths(env, paths, path_n_duplicate, x);
			else
			{
				// plong(1, x, '|');
				// plong(1, path_n_duplicate, '\n');
				// if (path_n > 0 && !ending_path(tmp_paths, path_n - 1, env->nb_rooms))
				// {
				// 	pstr(1, "entré dans le cas ou le chemin precedent n'est pas fini", '\n');
				// 	memcp(tmp_paths[path_n - 1], tmp_paths[path_n], sizeof(int) * env->nb_rooms);
				// 	int_set(tmp_paths[path_n], -1, env->nb_rooms);
				// }
				env->nb_valid++;
			}
		}
	}
	if (n_link == 0)
	{
		// printf("Would delete row: %d\n", path_n);
		// del_path(tmp_paths, path_n);
		// printf("path %d deleted cause no link\n", path_n);
	}
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path_to_dest(int **paths_src, int y_src, int **paths_dest, int y_dest, int until)
{
	memcp(paths_dest[y_dest], paths_src[y_src], (until) * sizeof(int));
	return (y_dest);
}

// allocate dynamically env->paths
int 	load_valid_paths(t_env *env, int **tmp_paths)
{
	int 	i;
	int 	j;
	int 	valid_saved;

	if (!(env->paths = alloc_matrix_int(env->nb_rooms, env->nb_valid, -1)))
		return 0;
	i = -1;
	valid_saved = 0;

	while (++i < (int)env->nb_rooms && valid_saved < env->nb_valid && (j = -1))
		while (++j < (int)env->nb_paths)
		{
			if (tmp_paths[j][i] == 1)
			{
				duplicate_path_to_dest(tmp_paths, j, env->paths, valid_saved, (int)env->nb_rooms);
				valid_saved++;
			}
		}
	return 1;
}

void 			init_links_matrix(t_env *env)
{
	t_parsed_link *l;

	if (!(env->links = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_rooms, 0)))
		return ;
	// printf("fpl before iteration: %p\n", &(env->first_parsed_link));
	l = env->first_parsed_link;
	// while (l && l->prev && l->prev->room)
	// 	l = l->prev;
	while (l && l->next && l->room1 && l->room2)
	{
		// printf("adding link between: %d-%d\n",l->room1->idx,l->room2->idx);
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
		l = l->next;
		// free(l->prev);
	}
	if (l && l->room1 && l->room2)
	{
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
		// free(l);
	}
	// printf("fpl after iteration: %p\n", &(env->first_parsed_link));
}
/*faut continuer fill name pour en faire un char * a fin , l'indice donne la room a print
**finir l'impression des fourmis en utilisant la colonie pour que ca ecrive au fur et a mesure
*/
void			init_name_tab(t_env *env)
{
	int				i;
	t_parsed_room	*r;

	i = -1;
	r = env->first_parsed_room;
	(env->room_names = alloc_matrix_char(256, env->nb_rooms))
	? 0 : perr(env, "Error: alloc_matric_char failed");
	while (++i < env->nb_rooms)
	{
		env->room_names[i] = memcp(env->room_names[i], r->room->id, 256);
		r = r->next;
	}
	free_parsed_rooms(env);
}

void         get_flow_max(t_env *env)
{
    int     i;
    int     flow_end;
	int		**tmp_node_exploration;

	(tmp_node_exploration = alloc_matrix_int(2, env->nb_rooms, -1))
	? 0 : perr(env, "Error: alloc_matric_int failed");
    env->flow_start_max = 0;
    flow_end = 0;
    i = 0;
    while (i < (int)env->nb_rooms)
    {
        if (env->links[0][i] == 1 && i != 0)
		{
			tmp_node_exploration[env->flow_start_max][0] = i;
			tmp_node_exploration[env->flow_start_max][1] = 0;
            env->flow_start_max++;
		}
        if (env->links[1][i] == 1 && i != 1)
            flow_end++;
        i++;
    }
	env->flow_max = flow_end <= env->flow_start_max ? flow_end : env->flow_start_max;
	env->node_exploration = alloc_matrix_int(2, env->flow_start_max, -1);
	i = -1;
	while (++i < env->flow_start_max)
		memcp(env->node_exploration[i], tmp_node_exploration[i], sizeof(int) * 2);
	// memcp(env->node_exploration, tmp_node_exploration, sizeof(int) * 2 * env->flow_start_max);
	free_matrix((void *)tmp_node_exploration, env->nb_rooms);
}

void			genetic_solve(t_env *env)
{
	int 	**tmp_paths;

	(tmp_paths = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_paths, -1)) ?
	0 : perr(env, "Error: tmp_paths malloc failed");
	explore_paths(env, tmp_paths, 0, 0);
	if (env->nb_valid < 1)
	{
		free_matrix((void *)tmp_paths, env->nb_paths);
		perr(env, "Error: no way out!");
	}
	if (!load_valid_paths(env, tmp_paths))
	{
		free_matrix((void *)tmp_paths, env->nb_paths);
		perr(env, "Error: failed loading valid paths into env->paths");
	}
	// print_matrix_int(tmp_paths, env->nb_rooms, env->nb_paths);
	free_matrix((void *)tmp_paths, env->nb_paths);
}
