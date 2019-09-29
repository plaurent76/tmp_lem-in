/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 17:15:21 by eviana            #+#    #+#             */
/*   Updated: 2019/09/29 18:50:34 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTHILL_H
# define ANTHILL_H

typedef struct s_graph t_graph;
typedef struct s_link t_link;
typedef struct s_ant t_ant;
typedef struct s_queue t_queue;
typedef struct s_paths t_paths;
typedef struct s_solut t_solut;
typedef struct s_env t_env;
typedef struct s_lines t_lines;

typedef struct		s_graph
{
	char			*name;
	int				visited;
	t_link			*link;
	int				x;
	int				y;
	int				ant;
	struct s_graph	*parent;
	struct s_graph	*next;
}					t_graph;

typedef struct		s_link
{
	int				len;
	int				flow;
	struct s_graph	*adjacent;
	struct s_link	*next;
}					t_link;

typedef struct		s_queue
{
	t_graph			*graph;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_paths
{
	int				len;
	t_link			*path;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_solut
{
	int				len;
	int				score;
	t_paths			*paths;
	struct s_solut	*next;
}					t_solut;

typedef struct		s_ant
{
	int				n;
	t_link			*path;
}					t_ant;

typedef struct		s_env
{
	t_graph			*graph;
	t_graph			*start;
	t_graph			*end;
	int				end_found;
	t_solut			*solut;
	t_solut			*best_solut;
	int				best_score;
	int				best_flow;
	t_ant			**colony;
	t_lines			*first_line;
	int				new_line;
	int				flow_max;
	int				option;
	int				nb_ants;
	int				t_len;
}					t_env;

typedef struct		s_lines
{
	char			*txt;
	struct s_lines	*prev;
	struct s_lines	*next;
}					t_lines;

#endif
