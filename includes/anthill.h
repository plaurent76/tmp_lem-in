/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviana <eviana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:39:17 by eviana            #+#    #+#             */
/*   Updated: 2019/08/22 13:39:17 by eviana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTHILL_H
# define ANTHILL_H

typedef struct s_path			t_path;
typedef struct s_room			t_room;
typedef struct s_ant			t_ant;
typedef struct s_env			t_env;
typedef struct s_link			t_link;
typedef struct s_lines			t_lines;
typedef struct s_parsed_room	t_parsed_room;
typedef struct s_parsed_link	t_parsed_link;

struct			s_env
{
	t_room			*start;
	t_room			*end;
	t_path			*fw;
	t_lines			*first_line;
	t_parsed_room	*first_parsed_room;
	t_parsed_room	*last_parsed_room;
	t_parsed_link	*first_parsed_link;
	t_parsed_link	*last_parsed_link;

	int				new_line;
	int				*best_combo;
	int				best_score;
	int				best_flow;
	int				flow_max;
	int				flow_start_max;
	int 			lpri;
	int				option;
	int				nb_rooms;
	int				nb_ants;
	int				nb_paths;
	int				max_paths_per_node;
	int				**node_exploration;
	int 			nb_valid;
	int				**links;
	int 			**paths;
	char			**room_names;
	char 			*room_free;
	t_ant			**colony;
};

struct			s_room
{
	char			id[256];
	int 			idx;
	int				x;
	int				y;
	t_ant			*ant;
	t_link			*link;
};

struct			s_parsed_room
{
	t_room			*room;
	t_parsed_room	*prev;
	t_parsed_room	*next;
};

struct			s_link
{
	t_room			*room;
	t_link			*prev;
	t_link			*next;
};

struct			s_lines
{
	char			*txt;
	t_lines			*prev;
	t_lines			*next;
};

struct			s_parsed_link
{
	t_room			*room1;
	t_room			*room2;
	t_parsed_link	*prev;
	t_parsed_link	*next;
};

struct			s_ant
{
	int				n;
	t_path			*path;
};

struct			s_path
{
	int				*rooms;
	int				size;
	int				current;
};

#endif