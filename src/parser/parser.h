/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:28 by bprovoos      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/11/03 17:46:15 by dyeboa        ########   odam.nl         */
=======
/*   Updated: 2022/11/03 14:05:44 by bprovoos      ########   odam.nl         */
>>>>>>> fc121cfdfff8a2bd03b05df1e44f5e67393c9115
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
	e_start = -1,	
	e_cmd,
	e_file,
	e_pipe,
	e_word,			// also flags for commands
	e_var,
	e_redirect_I,
	e_redirect_O,
	e_delimiter,
	e_append
}	note_type;

/* The parser processes the input line and build the list with tokens */
t_line_lst	*parser(char *line);

void		delete_t_list(t_line_lst **head);
<<<<<<< HEAD
void		add_at_end_of_list(t_line_lst **head, int type, char *value);
void		show_t_list(t_line_lst *node);
int			length_of_list(t_line_lst *node);
=======

void		show_t_list(t_line_lst *node);
>>>>>>> fc121cfdfff8a2bd03b05df1e44f5e67393c9115

#endif
