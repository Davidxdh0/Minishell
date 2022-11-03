/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/02 14:52:41 by bprovoos      ########   odam.nl         */
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
	printf("\n-- double array with tokens --\n");
	while (tokens[i])
	{
		printf("\t'%s'\n", tokens[i]);
		i++;
	}
	printf("---- end of double array -----\n");
}

// char	**test_token_array(void)
// {
// 	int		amount_of_tokens;
// 	char	**tokens;

// 	amount_of_tokens = 5;
// 	tokens = (char **)malloc(sizeof(char *) * (amount_of_tokens + 1));
// 	tokens[0] = ft_strdup("ls -la");
// 	tokens[1] = ft_strdup("|");
// 	tokens[2] = ft_strdup("grep Nov");
// 	tokens[3] = ft_strdup("|");
// 	tokens[4] = ft_strdup("grep m");
// 	tokens[5] = NULL;
// 	return (tokens);
// }

// char	**lexer(char *line)
// {
// 	int		amount_of_tokens;
// 	char	**tokens;

// 	amount_of_tokens = count_tokens(line);
// 	// tokens = test_token_array();
// 	// show_tokens(tokens);
// 	tokens = NULL;
// 	return (tokens);
// }
