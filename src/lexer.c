/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/13 15:35:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
	The lexer takes the input line and puts the characters together into words 
	called tokens.
*/
void	lexer(t_line *line, t_line_lst *line_lst)
{
	size_t	index;

	index = 0;
	while (index < line->size)
	{
		index++;
	}
	line_lst->value = line->str;
}
