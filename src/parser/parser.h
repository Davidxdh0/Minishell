/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 08:44:10 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASER_H
# define PASER_H

# include <stdlib.h>

typedef struct s_line_lst
{
	int					type;
	char				*value;
	struct s_line_lst	*next;
	struct s_line_lst	*prev;
}	t_line_lst;

/* Add a node after a given node */
t_line_lst	*insert_node_after(t_line_lst *node);

/* Add a node at the end */
t_line_lst	*add_node_end(t_line_lst *node);

/* Add a node before a given node */
t_line_lst	*insert_node_before(t_line_lst *node);

/* Add a node at the front */
t_line_lst	*add_node_front(t_line_lst *node);

/* Remove given node */
t_line_lst	*remode_node(t_line_lst *node);

/* Remove the list */
t_line_lst	*remove_list(t_line_lst *node);

/* Count length of list */
int			len_of_list(t_line_lst *node);

/* The parser processes the tokens build the list with */
t_line_lst	*parser(char **tokens);

#endif
