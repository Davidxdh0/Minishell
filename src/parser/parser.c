/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 20:20:28 by bprovoos      ########   odam.nl         */
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

/*
	The parser processes the tokens according to a grammar and build the command 
	table.
*/
t_line_lst	*parser(char	**tokens)
{
	int			list_len;
	t_line_lst	*line_lst;

	list_len = amount_of_tokens(tokens);
	line_lst = NULL;
	line_lst = (t_line_lst *)malloc(sizeof(t_line_lst));
	// line_lst_>value = "";
	show_line_lst(line_lst);
	return (line_lst);
}
