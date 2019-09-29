/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:39:30 by eviana            #+#    #+#             */
/*   Updated: 2019/09/29 16:49:28 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** DEPENDENCIES
*/
# include "anthill.h"
# include "libft.h"
# include "ft_printf.h"
# define IS_SET_U		(env->option & (1 << 0))
# define IS_SET_M		(env->option & (1 << 1))
# define IS_SET_A		(env->option & (1 << 2))
# define IS_SET_L		(env->option & (1 << 3))
# define IS_SET_R		(env->option & (1 << 4))
# define IS_SET_V		(env->option & (1 << 6))
# define IS_SET_H		(env->option & (1 << 7))
# define IS_SET_E		(env->option & (1 << 8))
# define SET_U			(env->option |= (1 << 0))
# define SET_M			(env->option |= (1 << 1))
# define SET_A			(env->option |= (1 << 2))
# define SET_L			(env->option |= (1 << 3))
# define SET_R			(env->option |= (1 << 4))
# define SET_V			(env->option |= (1 << 6))
# define SET_H			(env->option |= (1 << 7))
# define SET_E			(env->option |= (1 << 8))

/*
** BASICS
*/
int				*alloc_array_int(int n, int val);
int				*int_set(int *tab, int val, int size);
void			free_matrix(void **mx, int depth);
long			labs(long n);
int				active_bits(int c);
int				is_space(const char c);
int				is_digit(const char c);
int				sp_putlong(int fd, long n, char end);
int				sp_putstr(int fd, const char *s, char end);
int				sp_strcpy(char *dest, const char *src, char c);
long			fatol(t_env *env, const char *str);
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
void			perr(t_env *env, const char *err_msg);
int				anthill_complete(t_env *env);

/*
** LINKS
*/
void			add_link(t_link **src, t_link *new);
t_link			*new_link(t_env *env, t_graph *room);

/*
** ROOMS
*/
t_link			*link_search(t_graph *graph, char *name);
void			add_room(t_env *env, t_graph *new, int state);
t_graph			*new_room(t_env *env, char *name, long x, long y);
t_graph			*str_to_room(t_env *env, const char *s);
int				room_id_error(t_env *env, int room_id);
int				is_room_free(t_env *env, int room_id);
int				set_room_free(t_env *env, int room_id);
int				set_room_busy(t_env *env, int room_id);

/*
** ANTS
*/
int				move_ant_forward(t_env *env, t_ant *ant);
t_ant			*new_ant(t_env *env, t_link *path);
void			del_ant(t_ant *ant);

/*
** PATHS
*/
t_paths			*new_path(t_env *env, t_link *path);
void			del_path(t_link **path);
t_link			*extract_path(t_env *env, t_link *path, t_graph *cur, t_graph *tmp_g);

/*
** PRINT
*/
void			print_array_int(int *array, int n);
void			print_matrix_int(int **mx, int x, int y);
void			print_matrix_char(char **mx, int x, int y);
void			print_solut(t_solut *solut, int *ants_per_path);
void			print_rooms(t_graph *graph);

/*
** SOLVE
*/
t_graph			*next_room_queue(t_queue **queue);
void			add_to_queue(t_env *env, t_queue **queue, t_graph *graph);
void			assign_colony(t_env *env);
void			move_colony(t_env *env);
int				ed_karp(t_env *env);
void			extract_solut(t_env *env, int flow_max);
t_solut			*new_soluc(t_env *env, t_paths *paths, int flow_max);
t_paths			*extract_paths(t_env *env);

#endif
