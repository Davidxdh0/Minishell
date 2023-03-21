/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/21 14:34:52 by dyeboa        ########   odam.nl         */
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

// count de commands tot |. if | count as 1.
// malloc per command de **cmd
// fil per command de cmd
int		count_commands(t_line_lst *head)
{
	int i;

	t_line_lst *temp;
	temp = head;
	i = 0;
	while (temp && ft_strncmp(temp->value,"|", 1))
	{
		i++;
		printf("value = %s\n", temp->value);
		temp = temp->next;
	}
	return (i);
}

void	alloc_execute_list(t_line_lst *head)
{
	int i;
	int k;
	t_execute *cmdlist;

	cmdlist = malloc(sizeof(t_execute));
	while (head != NULL)
	{
		i = count_commands(head);
		if (i == 0)
			i++;
		k = 0;
		cmdlist->cmd = malloc(sizeof(char *) * i + 1);
		while (k < i && head)
		{
			cmdlist->cmd[k] = head->value;
			head = head->next;
			k++;
			printf("cmdlist->cmd[%d] == %s\n", k, cmdlist->cmd[k]);
		}
		if (head && !ft_strncmp(head->value,"|", 1))
		{
			printf("value | == %s\n", head->value);
		}
		cmdlist = cmdlist->next;
		cmdlist->next = NULL;
		head = head->next;
	}
}
// void	parser_acco(t_line_lst *head, char **envp)
// {
// 	int i;
// 	t_execute *cmdlist;

// 	t_line_lst *temp;
// 	temp = head;
// 	cmdlist->cmd = malloc(sizeof(t_execute));
// 	while (temp)
// 	{
// 		i = 0;
// 		if (temp->value != "|")
// 		{	
// 			i++;
// 		}
// 		temp = temp->next;
// 		cmdlist->cmd = malloc(sizeof(char *) * i + 1);
// 	}
// 	temp = head;
// 	while(temp)
// 	{
// 		if(temp->value != "|")
// 		{
// 			cmdlist->cmd[i] = temp->value;
// 			i++;
// 		}
// 		else
// 		{
// 			cmdlist = cmdlist->next;
// 			cmdlist->cmd
// 		}
// 		temp = temp->next;
// 	}
// }

// void	fill_parser(t_line_lst *head, char **envp)
// {

	
// }

int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;

	line_lst = parser(line);
	show_t_list(line_lst, line);
	// alloc_execute_list(line_lst);
	// printf("countcommands = %d", count_commands(line_lst));
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
		if (ft_strncmp(argv[0], "exit", 5))
			exit(1);
		shell(line, envp);
	}
	return (0);
}