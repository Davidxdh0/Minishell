/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 17:50:41 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
	The parser processes the tokens according to a grammar and build the command 
	table.
*/
t_line_lst	parser(char	**tokens)
{
	t_line_lst	line_lst;

	tokens = NULL;
	line_lst.value = "";
	return (line_lst);
}
