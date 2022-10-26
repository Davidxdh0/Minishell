/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/21 10:40:54 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_sure_line_is_empty(char **line)
{
	if (*line)
	{
		free (*line);
		*line = (char *) NULL;
	}
}

void	add_line_in_history(char **line)
{
	if (*line && **line)
		add_history (*line);
}

/*
	Set the display name in the termian and reading the input from the termial
*/
void	line_reader(char **line, const char *display_name)
{
	make_sure_line_is_empty(line);
	*line = readline (display_name);
	add_line_in_history(line);
}

/* Program flow
1. lexer
1.1. check syntax
1.2. puts the characters together into words called tokens
2. parser
2.1. read the tokens
2.2. build the command table
-------(index, command, flags, envp)
-------(in, out, err)
3. expander
4. executor
4.1. read command table
4.x. creating pipes
4.x. creating processes

To do:
[X] Header dependency in makefile
[X] Creata a flag option for giving command through argv
[ ] Make unit testers

Optional:
[ ] *.d files in seperate folder
*/
int	shell(char *line, char **envp)
{
	char	**tokens;

	tokens = lexer(line);
	envp = 0;
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
