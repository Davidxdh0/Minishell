/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/28 16:10:50 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	shell(char *line, char **envp)
{
	char		**tokens;
	t_line_lst	*line_lst;
	t_line_lst	*head;

	line_lst = NULL;
	tokens = lexer(line);
	head = parser(line_lst, tokens);
	test_list(head, envp);	// use for testing
	envp = NULL;
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;

	if (input_is_argv(argc, argv, &line))
		return (shell(line, envp));
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		shell(line, envp);
	}
	return (0);
}
