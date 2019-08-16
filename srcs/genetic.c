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
#include <stdio.h>

// static int		free_gen(t_path **gen, int gen_size, int ret)
// {
// 	while (--gen_size >= 0)
// 		gen[gen_size] ? del_path(gen[gen_size]) : 0;
// 	gen ? free(gen) : 0;
// 	return (ret);
// }

// static int		generate(t_env *env, t_path *parent, t_path **p, t_link *l)
// {
// 	*p = add_path(env, duplicate_path(env, parent), l->room);
// 	if ((*p)->room == env->end)
// 	{
// 		if (path_len(env->fw) == -1 ||
// 			(path_len(*p) < path_len(env->fw)))
// 		{
// 			del_path(env->fw);
// 			env->fw = duplicate_path(env, *p);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// static int		next_gen(t_env *env, t_path *parent, int gen_size, int i)
// {
// 	t_path	**p;
// 	t_link	*l;

// 	if (!(parent && parent->room && parent->room->link))
// 		put_error(env, "Error: cannot make new gen from this parent");
// 	(p = (t_path **)malloc(sizeof(t_path *) * gen_size))
// 	? 0 : put_error(env, "Error: t_path ** malloc failed");
// 	l = parent->room->link;
// 	while (l && l->prev && l->prev->room)
// 		l = l->prev;
// 	while (++i < gen_size && l && l->room)
// 	{
// 		if ((in_path(parent, l->room) == 1))
// 		{
// 			p[i] = NULL;
// 			l = l->next;
// 			continue;
// 		}
// 		if ((generate(env, parent, &p[i], l) || (path_len(env->fw) > 0
// 			&& path_len(p[i]) >= path_len(env->fw))))
// 			return (env->fw ? free_gen(p, i + 1, 1) : free_gen(p, i + 1, 0));
// 		next_gen(env, p[i], count_rooms(p[i]->room), -1);
// 		l = l->next;
// 	}
// 	return (env->fw ? free_gen(p, gen_size, 1) : free_gen(p, gen_size, 0));
// }

int		**alloc_matrix_int(int x, int y, int id)
{
	int		i;
	int		j;
	int		**matrix;
	
	i = 0;
	if (!(matrix = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	while (i < y)
	{
		j = 0;
		if (!(matrix[i] = (int*)malloc(sizeof(int) * x)))
			return (NULL);
		while (j < x)
			matrix[i][j++] = id;
		i++;
	}
	return (matrix);
}

char	**alloc_matrix_char(int x, int y)
{
	int		i;
	char	**matrix;
	
	i = 0;
	if (!(matrix = (char**)malloc(sizeof(char*) * y)))
		return (NULL);
	while (i < y)
	{
		if (!(matrix[i] = (char*)malloc(sizeof(char) * x)))
			return (NULL);
		mems(matrix[i], 0, x);
		i++;
	}
	return (matrix);
}

void	free_matrix(int ***tab, int depth)
{
	while (--depth >= 0)
		free((*tab)[depth]);
	free(*tab);
	*tab = NULL;
}

int	 ffy(int **mx, int size_y)
{
	int i = -1;

	while (++i < size_y) {
		if (mx[i][1] == -1) {
			return i;
		}
	}
	return -1;
}

int	 ffx(int **mx, int y, int size_x)
{
	int i = -1;

	while (++i < size_x) {
		if (mx[y][i] == -1) {
			return i;
		}
	}
	return 0;
}

int		ending_path(int **mx, int y, int size_m)
{
	int		i;

	i = -1;
	while (i < size_m && mx[y][++i] != -1)
	{
		if (mx[y][i] == 1 || i + 1 == size_m)
			return (1);
	}
	return (0);
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path_until(int **mx, int until, int size_y, int y_src)
{
	int 	y;
	// int		*tmp;

	// tmp = NULL;
	y = ffy(mx, size_y);
	if (y == -1)
		return -1;
	// 
	// else
		memcp(mx[y], mx[y_src], (until) * sizeof(int));
	return (y);
}

void 	print_path(int *path, int n)
{
	int i = -1;

	while (++i < n)
		(i == (n-1)) ? printf("%d\n", path[i]) : printf(" %d\t| ", path[i]);
}

void 	print_tab(int **tab, int x, int y)
{
	int i = -1;

	while (++i < y)
	{
		printf("%d\t | ", i);
		print_path(tab[i], x);
	}
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
int		room_used(int **mx, int path_n, int until, int id)
{
	int 	length;

	length = -1;
	while (++length < until && mx[path_n][length] != -1)
	{
		if (mx[path_n][length] == id)
		{
			// printf("room %d found in path %d at length %d: ", id, path_n, length);
			// print_path(mx[path_n], length + 1);
			return (1);
		}
	}
	// length = length < until ? length : until;
	// printf("room %d NOT found in path %d of length %d: ", id, path_n, length);
	// print_path(mx[path_n], length);
	if (path_n > 0) {
		//printf("path_n: %d length: %d\n", path_n, length);
		if (paths_match(mx[path_n], mx[path_n - 1], length)
			&& (id == mx[path_n - 1][length])) {
			return (1);
		}
		//bullshit
		// printf("comparing previous path:\n");
		// print_path(mx[path_n-1], length);
		// printf("with new path:\n");
		// print_path(mx[path_n], length);
		// printf("path_match:%s\n", paths_match(mx[path_n], mx[path_n - 1], length) ? "yes\n" : "no\n");

		// printf("comparing last room of previous with new room to add:\n");
		// printf("%d vs %d match:%s\n", id, mx[path_n - 1][length], (id == mx[path_n - 1][length]) ? "yes\n" : "no\n");
		// //end of bullshit

	}
	
	return (0);
}

// void	del_path(int **mx, int y)
// {
// 	int 	i;

// 	i = -1;
// 	while (mx[y][++i] > -1)
// 	{
// 		mx[y][i] = -1;
// 	}
// }

void	add_to_path(int **mx, int size_x, int y, int id)
{
	mx[y][ffx(mx, y, size_x)] = id;

}


void 	explore_paths(t_env *env, int **mx, int path_n, int id)
{
	int 	n_link;
	int 	path_n_duplicate;
	int		path_n_length;
	int		x;

	x = -1;
	n_link = 0;
	if (!path_n && mx[0][0] == -1)
	{
		path_n = ffy(mx, env->nb_paths);
		if (path_n == -1)
			return ;
		add_to_path(mx, env->nb_rooms, path_n, id);
	}
	path_n_duplicate = path_n;
	path_n_length = 0;
	while (path_n_length < env->nb_rooms && mx[path_n][path_n_length] != -1)
		path_n_length++;
	while (++x < (int)env->nb_rooms)
	{
		// checks if room is already in path and if path is not duplicate from last one
		if (env->links[id][x] && !room_used(mx, path_n, env->nb_rooms, x)) // link exists with start
		{
			//if (id == 0)
				//printf("%d\n", x);
			//printf("%d-%d\n", id, x);
			++n_link;
			if (n_link > 1)
				path_n_duplicate = duplicate_path_until(mx, path_n_length, env->nb_paths, path_n);
			if (path_n_duplicate == -1)
				return ;
			add_to_path(mx, env->nb_rooms, path_n_duplicate, x);
			// print_tab(mx, env->nb_rooms, env->nb_paths);
			// printf("explore path %d from room %d\n", path_n, x);
			if (x != 1)
				explore_paths(env, mx, path_n_duplicate, x);
			else
			{
				plong(1, x, '|');
				plong(1, path_n_duplicate, '\n');
				if (path_n > 0 && !ending_path(mx, path_n - 1, env->nb_rooms))
				{
				pstr(1, "entrer dans le cas ou le chemins precedent n'est pas fini", '\n');
					// mx[path_n - 1] = memcp(mx[path_n - 1], mx[path_n], sizeof(int) * env->nb_rooms);
					// mx[path_n] = mems(mx[path_n], (char)-1, env->nb_rooms);
				}
				env->nb_valid++;
			}
		}
	}
	if (n_link == 0)
	{
		// del_path(mx, path_n);
		//printf("path %d deleted cause no link\n", path_n);
	}
}

// first valid from
int 	fvf(int **mx, int from, int size_x, int size_y)
{
	int i;
	int j;

	j = from;
	while (j++ < size_y)
	{
		i = -1;
		while (++i < size_x)
			if (mx[j][i] == 1)
				return j;
	}
	return -1;
}

// duplicates given path row and returns index of duplicated row
int		duplicate_path_to_dest(int **mx_src, int y_src, int **mx_dest, int y_dest, int until)
{
	memcp(mx_dest[y_dest], mx_src[y_src], (until) * sizeof(int));
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

	while (++i < (int)env->nb_rooms && valid_saved < env->nb_valid)
	{
		j = -1;
		while (++j < (int)env->nb_paths)
		{
			if (tmp_paths[j][i] == 1)
			{
				duplicate_path_to_dest(tmp_paths, j, env->paths, valid_saved, (int)env->nb_rooms);
				valid_saved++;
			}
		}
	}
	return 1;
}

void 			fill_links_matrix(t_env *env)
{
	t_parsed_link *l;

	if (!(env->links = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_rooms, 0)))
		return ;
	l = env->first_parsed_link;
	// while (l && l->prev && l->prev->room)
	// 	l = l->prev;
	while (l && l->next && l->room1 && l->room2)
	{
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
		l = l->next;
	}
	if (l && l->room1 && l->room2)
	{
		env->links[l->room1->idx][l->room2->idx] = 1;
		env->links[l->room2->idx][l->room1->idx] = 1;
	}
}
/*faut continuer fill name pour en faire un char * a fin , l'indice donne la room a print
**finir l'impression des fourmis en utilisant la colonie pour que ca ecrive au fur et a mesure
*/
void			fill_name_tab(t_env *env)
{
	int		i;

	i = 0;
	env->room_names = alloc_matrix_char(256, env->nb_rooms);
	while (i < env->nb_rooms)
	{
		env->room_names[i] = memcp(env->room_names[i], env->first_parsed_room->room->id, 256);
		env->first_parsed_room = env->first_parsed_room->next;
		// pstr(1, env->room_names[i], (char)1);
		i++;
	}
}

void         count_flow_max(t_env *env)
{
    int     i;
    int     flow_start;
    int     flow_end;

    flow_start = 0;
    flow_end = 0;
    i = 0;
    while (i < (int)env->nb_rooms)
    {
        if (env->links[0][i] == 1 && i != 0)
            flow_start++;
        if (env->links[1][i] == 1 && i != 1)
            flow_end++;
        i++;
    }
    if (flow_end <= flow_start)
        env->flow_max = flow_end;
    else
        env->flow_max = flow_start;
}

void			genetic_solve(t_env *env)
{
	// t_path *init;

	// init = new_path(env);
	// (init && init->room && init->room->link && init->room->link)
	// ? 0 : put_error(env, "Error: faulty path init");
	// if (!next_gen(env, init, count_rooms(init->room), -1))
	// 	put_error(env, "Error: no way out");
	// del_path(init);

	int 	**tmp_paths;

	env->nb_rooms = env->lpri + 1;
	// alloc room_free to track room occupation
	env->room_free = (char *)malloc(sizeof(char)*env->nb_rooms);
	mems(env->room_free, (char)1, env->nb_rooms);
	env->nb_paths = (int)(248 + env->nb_rooms / 2);
	fill_links_matrix(env);
	count_flow_max(env);
	fill_name_tab(env);
	if (!(tmp_paths = alloc_matrix_int((int)env->nb_rooms, (int)env->nb_paths, -1)))
		return ;
	//  print_tab(tmp_paths, env->nb_rooms, env->nb_paths);
	print_tab(env->links, env->nb_rooms, env->nb_rooms);
	explore_paths(env, tmp_paths, 0, 0);
	 print_tab(tmp_paths, env->nb_rooms, env->nb_paths);
	if (!load_valid_paths(env, tmp_paths))
		printf("error loading valid paths into env->paths");
	// print summary
	printf("nb_rooms: %d | nb_paths (max): %d | nb_paths (used): %d\n"
		, env->nb_rooms, env->nb_paths, ffy(env->paths, env->nb_valid));
	// print valid paths:
	printf("found %d valid paths:\n", env->nb_valid);
	print_tab(env->paths, env->nb_rooms, env->nb_valid);
	// print all paths:
	// printf("all paths:\n");
	// print_tab(tmp_paths, env->nb_rooms, env->nb_paths);
	free_matrix(&tmp_paths, env->nb_paths);
	free_matrix(&env->links, env->nb_rooms);
	//free_matrix(&env->paths, env->nb_valid);
	return ;
}
