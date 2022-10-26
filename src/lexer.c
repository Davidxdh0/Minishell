/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 13:42:36 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	count_tokens(char *line)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '"' || line[index] == '\'')
			get_data_in_quotes(&line[index]);
		ft_putchar_fd(line[index], 1);
		index++;
	}
	ft_putchar_fd('\n', 1);
	return (counter);
}

/*
	The lexer takes the input line and puts the characters together into words 
	called tokens.
*/
char	**lexer(char *line)
{
	char	**tokens;

	count_tokens(line);
	tokens = NULL;
	// tokens = malloc(sizeof(char *) * count_tokens(line));
	return (tokens);
	// return (ft_split(line, ' '));
}
