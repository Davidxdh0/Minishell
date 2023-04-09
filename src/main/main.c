/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/02 08:11:53 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// count de commands tot |. if | count as 1.
// malloc per command de **cmd
// fil per command de cmd
int		count_commands(t_line_lst *head)
{
	int i;

	t_line_lst *temp;
	temp = head;
	i = 0;
	// if (temp && !ft_strncmp(temp->value,"|", 1))
	// 	return (1);
	while (temp && ft_strncmp(temp->value,"|", 1))
	{
		i++;
		// printf("value = %s\n", temp->value);
		temp = temp->next;
	}
	return (i);
}

t_execute *alloc_execute_list(t_line_lst *head)
{
	int i;
	int k;
	t_execute *cmdlist = NULL;
 	t_execute *last = NULL;
	
	while (head != NULL)
	{
		i = count_commands(head);
		k = 0;
		t_execute *new_node = malloc(sizeof(t_execute));
        new_node->cmd = malloc(sizeof(char *) * (i + 1));
        new_node->next = NULL;
		while (head != NULL && k < i)
		{
            new_node->cmd[k] = ft_strdup(head->value);
            // printf("new_node->cmd[%d] == %s\n", k, new_node->cmd[k]);
            head = head->next;
            k++;
		}
		new_node->cmd[k] = NULL;
		if (last == NULL)
            cmdlist = new_node;
        else
            last->next = new_node;
		last = new_node;
		if (head != NULL && !ft_strncmp(head->value,"|", 1))
			;// printf("value head == %s\n", head->value);
		if (head != NULL)
			head = head->next;
	}
	
	return (cmdlist);
}

int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;

	line_lst = parser(line);
	show_t_list(line_lst, line);
	cmd = alloc_execute_list(line_lst);

	executor_dcs(cmd, envp); //DCS

	// execute_cmd_list(cmd, &data);
	// if (!is_valid_grammer(line_lst))
	// 	return (1);
	// test_lists(line_lst, envp);
	
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
