/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:19:58 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:20:00 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** DEPENDENCIES
*/

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "anthill.h"

/*
** MACROS
*/

# define R1 (env->first_parsed_room)
# define R2 (env->last_parsed_room)
# define L1 (env->first_parsed_link)
# define L2 (env->last_parsed_link)

# define IS_SET_U		(env->option & (1 << 0))
# define IS_SET_M		(env->option & (1 << 1))
# define IS_SET_A		(env->option & (1 << 2))
# define IS_SET_L		(env->option & (1 << 3))
# define IS_SET_R		(env->option & (1 << 4))
# define IS_SET_S		(env->option & (1 << 5))
# define IS_SET_V		(env->option & (1 << 6))
# define IS_SET_H		(env->option & (1 << 7))
# define IS_SET_E		(env->option & (1 << 8))

# define SET_U			(env->option |= (1 << 0))
# define SET_M			(env->option |= (1 << 1))
# define SET_A			(env->option |= (1 << 2))
# define SET_L			(env->option |= (1 << 3))
# define SET_R			(env->option |= (1 << 4))
# define SET_S			(env->option |= (1 << 5))
# define SET_V			(env->option |= (1 << 6))
# define SET_H			(env->option |= (1 << 7))
# define SET_E			(env->option |= (1 << 8))

/*
** BASICS
*/

int		        *alloc_array_int(int n, int val);
char	        *alloc_array_char(int n, char val);
int		        **alloc_matrix_int(int x, int y, int val);
char            **alloc_matrix_char(int x, int y);
int             *int_set(int *tab, int val, int size);
void	        free_matrix_int(int ***tab, int depth);
int				slen(char *s);
long			labs(long n);
int				active_bits(char c);
int				is_space(const char c);
int				is_digit(const char c);
int				plong(int fd, long n, char end);
int				pstr(int fd, const char *s, char end);
int				scat(char *dest, const char *src, char c);
long			fatol(t_env *env, const char *str);
int				scmp(const char *s1, const char *s2);
void			*memcp(void *mem2, const void *mem1, int n);
void			*mems(void *mem, int c, size_t n);
void			init_env(t_env *env);
void			deinit_env(t_env *env);

/*
** IO
*/

int				interpret_line(t_env *env, const char *p);
void			free_lines(t_env *env);
int				get_lines(t_env *env);
void			put_lines(t_env *env);

/*
** ERROR MANAGEMENT
*/

void			sig_handler(int sig);
void			put_usage(t_env *env);
void			put_error(t_env *env, const char *err_msg);
int				anthill_complete(t_env *env);

/*
** LINKS
*/

t_link			*add_link(t_room *new_room, t_link *prev_link);
void			new_link(t_env *env, t_room *room1, t_room *room2);
void			link_rooms(t_env *env, t_room *room1, t_room *room2);
int				count_rooms(t_room *room);
void			free_room_links(t_env *env, t_room *room);

/*
** ROOMS
*/

void			new_room(t_env *env, char *name, long x, long y, int state);
t_room			*str_to_room(t_env *env, const char *s);

/*
** ANTS
*/

void			ant_add_path(t_env *env, t_ant *ant, t_room *room);
int				move_ant_forward(t_env *env, t_ant *ant);
t_ant			*new_ant(t_env *env, int *path, int size);
void			del_ant(t_env *env, t_ant *ant);

/*
** PATHS
*/

t_path			*new_path(t_env *env, int *path, int size);
t_path			*duplicate_path(t_env *env, t_path *path);
t_path			*add_path(t_env *env, t_path *path, t_room *room);
int				in_path(t_path *path, t_room *r);
int				path_len(int *path, int size);
void			del_ant_path(t_path *path);
void			put_path(t_path *path);

/*
** PRINT
*/
void            print_array_int(int *array, int n);
void            print_matrix_int(int **mx, int x, int y);
void			put_fwinfo(t_env *env);
void			put_ants(t_env *env);
void			put_all(t_env *env);
void			put_ant(t_env *env, t_ant *ant);
void			put_room(t_env *env, t_room *r);
void			put_rooms(t_env *env);
void			put_link(t_env *env, t_parsed_link *l);
void			put_links(t_env *env);
void			put_room_links(t_env *env, t_room *room);

/*
** SOLVE
*/

void			brute_solve(t_env *env);
void			genetic_solve(t_env *env);
void            assign_colony(t_env *env);
void			move_colony(t_env *env);
void            combo_optimal(t_env *env);

#endif
