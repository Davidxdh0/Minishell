/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/17 15:25:52 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//global variable env?

int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;

	line_lst = parser(line);
	show_t_list(line_lst, line);
	// if (!is_valid_grammer(line_lst))
	// 	return (1);
	// test_lists(line_lst, envp);
	// execute_cmd_list(line_lst, &data);
	delete_t_list(&line_lst);
	envp++;	// temp until using envp
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;

	if (!*envp)
		return (1);
	g_data.exitcode = 0;
	g_data.envp = envp;
	if (input_is_argv(argc, argv, &line))
		return (shell(line, envp));
	while (1)
	{	
		line_reader(&line, "minishell$ ");
		shell(line, envp);
	}
	return (0);
}