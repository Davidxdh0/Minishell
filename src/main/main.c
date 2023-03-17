/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/17 18:23:40 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//global variable env?

void	test_lists(t_line_lst *head, char **envp)
{
	g_data.envp = envp;
	head = NULL;
	add_at_end_of_list(&head, e_cmd, "ls");
	add_at_end_of_list(&head, e_word, "ls -l");
	add_at_end_of_list(&head, e_cmd, "cd .");
	//add_at_end_of_list(&head, e_cmd, "pwd");
	add_at_end_of_list(&head, e_cmd, "echo");
	add_at_end_of_list(&head, e_cmd, "ls");
	// add_at_end_of_list(&head, e_word, "-la");
	// add_at_end_of_list(&head, e_pipe, "|");
	// add_at_end_of_list(&head, e_cmd, "grep");
	// add_at_end_of_list(&head, e_word, "17");
	// add_at_end_of_list(&head, e_cmd, "grep gitignore");
	//add_at_end_of_list(&head, e_file, "outfile.txt");
	show_t_list(head, "Put here the input line as reference");
	printf("length of list is %d\n", length_of_list(head));
	execute_cmd_list(head, &g_data);
	//delete_list(&head);
	//show_list(head);
	//printf("length of list is %d\n", length_of_list(head));
}


int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;

	line_lst = parser(line);

	show_t_list(line_lst, line);
	// if (!is_valid_grammer(line_lst))
	// 	return (1);
	test_lists(line_lst, envp);
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