/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 10:45:41 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
	The lexer takes the input line and puts the characters together into words 
	called tokens.
*/
void	lexer(char *line, char **tokens)
{
	int	i;

	tokens = ft_split(line, ' ');
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
}
