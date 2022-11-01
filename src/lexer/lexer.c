/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/31 17:41:20 by yeboa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>	// temp

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
		ft_putchar_fd('\n', 1);
	}
	return (counter);
}

void	free_double_char_array(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	show_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("tokens\n");
	while (tokens[i])
	{
		printf("\t'%s'\n", tokens[i]);
		i++;
	}
}

void	test_token_input(void)
{
	int		amount_of_tokens;
	char	**tokens;

	amount_of_tokens = 3;
	tokens = (char **)malloc(sizeof(char *) * (amount_of_tokens + 1));
	tokens[0] = ft_strdup("ls -la");
	tokens[1] = ft_strdup(">");
	tokens[2] = ft_strdup("outfile.txt");
	tokens[3] = NULL;
	show_tokens(tokens);
}

char	**lexer(char *line)
{
	int		amount_of_tokens;
	char	**tokens;

	amount_of_tokens = count_tokens(line);
	tokens = NULL;
	amount_of_tokens++;
	// test_token_input();
	return (tokens);
}
