/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 14:44:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASER_H
# define PASER_H

# include <stdlib.h>

/*
	+------+-------+------+     +------+-------+------+     +------+-------+------+
	| prev | type  | next | <-> | prev | type  | next | <-> | prev | type  | next |
	+------+       +------+     +------+       +------+     +------+       +------+
	       | value |                   | value |                   | value |       
	       +-------+                   +-------+                   +-------+       
*/
typedef struct s_line_lst
{
	int					type;
	char				*value;
	struct s_line_lst	*next;
	struct s_line_lst	*prev;
}	t_line_lst;

typedef enum{
	empty = -1,
	cmd,
	file,
	pipe,
	text,
	var,
	redirect
}	note_type;

/* Add a node at the end */
void	add_node_end(t_line_lst **node);

/* Add a node before a given node */
void	insert_node_before(t_line_lst *node);

void	insert_node_after(t_line_lst *node);

/* Loop to the first node */
t_line_lst	*get_first_node(t_line_lst *node);

/* Add a node at the front */
void	add_node_front(t_line_lst *node);

/* Remove given node */
void	remode_node(t_line_lst *node);

/* Remove the list */
void	remove_list(t_line_lst *node);

/* Count length of list */
int		len_of_list(t_line_lst *node);

/* The parser processes the tokens build the list with */
t_line_lst	*parser(char **tokens);

#endif
