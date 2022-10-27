/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 08:40:57 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	Debug function for showing the information in te line list
*/
void	show_line_lst(t_line_lst *line_lst)
{
	line_lst->value = "";
}

int	amount_of_tokens(char **tokens)
{
	int	list_len;

	list_len = 0;
	tokens =  NULL;
	return (list_len);
}

/* Add a node after a given node */
t_line_lst	*insert_node_after(t_line_lst *node)
{
	
}

/* Add a node at the end */
t_line_lst	*add_node_end(t_line_lst *node)
{
	
}

/* Add a node before a given node */
t_line_lst	*insert_node_before(t_line_lst *node)
{
	
}

/* Add a node at the front */
t_line_lst	*add_node_front(t_line_lst *node)
{
	
}

/* Remove given node */
t_line_lst	*remode_node(t_line_lst *node)
{
	
}

/* Remove the list */
t_line_lst	*remove_list(t_line_lst *node)
{
	
}

/* Count length of list */
int			len_of_list(t_line_lst *node)
{
	
}

/*
	The parser processes the tokens build the list with .
*/
t_line_lst	*parser(char **tokens)
{
	int			len_list;
	t_line_lst	*line_lst;

	len_list = amount_of_tokens(tokens);
	line_lst = NULL;
	line_lst = (t_line_lst *)malloc(sizeof(t_line_lst));
	// line_lst_>value = "";
	show_line_lst(line_lst);
	return (line_lst);
}
