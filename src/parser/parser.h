/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/02 18:39:56 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASER_H
# define PASER_H

# include "../../libs/libft/libft.h"
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
	e_none = -1,
	e_cmd,
	e_file,
	e_pipe,
	e_text,
	e_var,
	e_redirect
}	note_type;

/* The parser processes the input line and build the list with tokens */
t_line_lst	*parser(char *line);

void		delete_list(t_line_lst **head);

void		show_list(t_line_lst *node);

#endif
