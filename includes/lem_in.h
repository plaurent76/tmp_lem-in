/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paullaurent <paullaurent@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 10:07:16 by plaurent          #+#    #+#             */
/*   Updated: 2019/10/07 11:56:43 by paullaurent      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "anthill.h"
# include "libft.h"
# include "ft_printf.h"

# define IS_SET_M		(env->option & (1 << 1))
# define IS_SET_C		(env->option & (1 << 2))
# define IS_SET_R		(env->option & (1 << 4))
# define IS_SET_V		(env->option & (1 << 6))
# define IS_SET_H		(env->option & (1 << 7))

# define SET_M			(env->option |= (1 << 1))
# define SET_C			(env->option |= (1 << 2))
# define SET_R			(env->option |= (1 << 4))
# define SET_V			(env->option |= (1 << 6))
# define SET_H			(env->option |= (1 << 7))

int				*alloc_array_int(int n, int val);
int				active_bits(int c);
int				is_space(const char c);
int				is_digit(const char c);
int				sp_putlong(int fd, long n, char end);
int				sp_putstr(int fd, const char *s, char end);
int				sp_strcpy(char *dest, const char *src, char c);
long			fatol(t_env *env, const char *str);
void			deinit_env(t_env *env);

int				interpret_line(t_env *env, const char *p);
void			free_lines(t_env *env);
int				get_lines(t_env *env);
void			put_lines(t_env *env);

void			put_usage(t_env *env);
void			perr(t_env *env, const char *err_msg);
int				anthill_complete(t_env *env);

void			add_link(t_link **src, t_link *new);
t_link			*new_link(t_env *env, t_graph *room);

t_link			*link_search(t_graph *graph, char *name);
void			add_room(t_env *env, t_graph *new, int state);
t_graph			*new_room(t_env *env, char *name, long x, long y);
t_graph			*str_to_room(t_env *env, const char *s);

int				move_ant_forward(t_env *env, t_ant *ant);
t_ant			*new_ant(t_env *env, t_link *path);
void			del_ant(t_ant *ant);

t_paths			*new_path(t_env *env, t_link *path);
void			del_path(t_link **path);
t_link			*extract_path(t_env *env, t_link *path,
		t_graph *cur, t_graph *tmp_g);

void			print_array_int(int *array, int n);
void			print_solut(t_solut *solut, int *ants_per_path);
void			print_rooms(t_graph *graph);

t_graph			*next_room_queue(t_queue **queue);
void			add_to_queue(t_env *env, t_queue **queue, t_graph *graph);
void			assign_colony(t_env *env);
void			move_colony(t_env *env);
int				ed_karp(t_env *env);
void			extract_solut(t_env *env, int flow_max);
t_solut			*new_soluc(t_env *env, t_paths *paths, int flow_max);

#endif
