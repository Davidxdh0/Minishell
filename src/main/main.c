/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/26 18:17:13 by dyeboa        ########   odam.nl         */
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
	while (temp != NULL && ft_strncmp(temp->value, "|", 1))
	{
		if (temp->state > 0)
		{
			while (temp != NULL && temp->state > 0)
				temp = temp->next;
			i++;
			if (!temp)
				return (i);
		}
		if (!ft_isredirect(temp->value))
			printf("dfd");
		if (temp != NULL)
			temp = temp->next;
		i++;
	}
	// printf("value2 = %s, %d\n", temp->value, i);
	return (i);
}

char *make_string(t_line_lst *line_lst)
{
	char *tempstring;

	if (line_lst->value)
		tempstring = ft_strdup(line_lst->value);
	while (line_lst != NULL && ft_strncmp(line_lst->value, "|", 1))
	{
		while (line_lst->next != NULL && line_lst->next->state > 0)
		{
			line_lst = line_lst->next;
			tempstring = ft_strjoin(tempstring, line_lst->value);
		}
		line_lst = line_lst->next;
	}
	// printf("string = %s\n", tempstring);
	return (tempstring);
}

int	ft_isredirect(char *str)
{
	if (ft_strcmp(str, ">") || ft_strcmp(str, ">>") || ft_strcmp(str, "<") || ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

char **make_redirects(t_line_lst *line_lst)
{
	char **tempstring;
	t_line_lst *temp;
	int i;

	i = 0;
	temp = line_lst;
	while (temp != NULL && ft_strcmp(line_lst->value, "|"))
	{
		if (ft_isredirect(line_lst->value))
			i++;
		else if (ft_isredirect(line_lst->prev->value))
			i++;
		temp = temp->next;
	}
	tempstring = malloc(sizeof(char **) * i + 1);
	temp = line_lst;
	i = 0;
	while (line_lst != NULL && ft_strncmp(line_lst->value, "|", 1))
	{
		if (ft_isredirect(line_lst->value))
			tempstring[i] = ft_strdup(line_lst->value);
		else if (ft_isredirect(line_lst->prev->value))
			tempstring[i] = ft_strdup(line_lst->value);
		i++;
		temp = temp->next;
	}
	// printf("string = %s\n", tempstring);
	return (tempstring);
}

t_execute *alloc_execute_list(t_line_lst *head)
{
	int k;
	t_execute *cmdlist = NULL;
 	t_execute *last = NULL;
	char *temp;
	while (head != NULL)
	{
		k = 0;
		t_execute *new_node = malloc(sizeof(t_execute));
		new_node->count_cmd = count_commands(head);
		new_node->cmd = malloc(sizeof(char *) * (new_node->count_cmd + 1));
        new_node->next = NULL;
		while (head != NULL && k < new_node->count_cmd )
		{
			if (head->state > 0)
			{
				temp = make_string(head);
				if (temp[0] == '\"' || temp[0] == '\'')
					new_node->cmd[k] = ft_substr(temp, 1, ft_strlen(temp) - 2);
				while (head != NULL && head->state > 0)
					head = head->next;
			}
			else
			{
            	new_node->cmd[k] = ft_strdup(head->value);
				head = head->next;
			}
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
	// printf("cmdlist = %s", cmdlist->cmd[0]);
	return (cmdlist);
}

int ft_arrlen(char **arr)
{
    int i = 0;
    while (arr[i] != NULL)
        i++;
    return (i);
}

int count_redirects(char **cmd_list)
{
    int num_redirects = 0;
    int i = 0;
    while (cmd_list[i])
    {
        if (!ft_strcmp(cmd_list[i], ">") || !ft_strcmp(cmd_list[i], ">>") || !ft_strcmp(cmd_list[i], "<") || !ft_strcmp(cmd_list[i], "<<"))
            num_redirects++;
        i++;
    }
    return (num_redirects);
}

t_execute *create_new_node(int num_commands, int num_redirects)
{
    t_execute *new_node = malloc(sizeof(t_execute));
    new_node->cmd = malloc(sizeof(char *) * (num_commands + 1));
    new_node->redirects = malloc(sizeof(char *) * (num_redirects * 2 + 1));
    new_node->next = NULL;
    return (new_node);
}

void copy_commands_and_redirects(t_execute *dest_node, char **cmd_list, int num_redirects)
{
    int i = 0;
    int j = 0;
    int cmd_index = 0;
    while (cmd_list[i])
    {
        if (!ft_strcmp(cmd_list[i], ">") || !ft_strcmp(cmd_list[i], ">>") || !ft_strcmp(cmd_list[i], "<") || !ft_strcmp(cmd_list[i], "<<"))
        {
            dest_node->redirects[j] = ft_strdup(cmd_list[i]);
            j++;
            i++;
            dest_node->redirects[j] = ft_strdup(cmd_list[i]);
            j++;
            num_redirects--;
        }
        else
        {
            dest_node->cmd[cmd_index] = ft_strdup(cmd_list[i]);
            cmd_index++;
        }
        i++;
    }
    dest_node->cmd[cmd_index] = NULL;
    dest_node->redirects[j] = NULL;
}

/*
** Splits a command list into separate nodes of commands and redirects
*/
t_execute *acco(t_execute *cmds)
{
    t_execute *new_list;
    t_execute *current_node;
    int num_redirects;
    int num_commands;

	current_node = NULL;
	new_list = NULL;
	num_redirects = 0;
	if (cmds == NULL)
		return (NULL);
    while (cmds != NULL)
    {
        num_commands = 0;
        num_redirects = count_redirects(cmds->cmd);
        num_commands = ft_arrlen(cmds->cmd) - num_redirects;
        if (new_list == NULL)
        {
            new_list = create_new_node(num_commands, num_redirects);
            current_node = new_list;
        }
        else
        {
            current_node->next = create_new_node(num_commands, num_redirects);
            current_node = current_node->next;
        }
        copy_commands_and_redirects(current_node, cmds->cmd, num_redirects);
        cmds = cmds->next;
    }
	if (num_commands == 0)
		new_list->cmd = NULL;
    return new_list;
}

void	show(t_execute *cmd)
{
	int i;
	// if (cmd == NULL)
	// 	return ;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->cmd != NULL && cmd->cmd[i] != NULL)
		{
			printf("cmd[%d] = %s\n", i, cmd->cmd[i]);
			i++;
		}
		i = 0;
		if (cmd->redirects != NULL && cmd->redirects[0] != NULL)
		{
			while (cmd->redirects != NULL && cmd->redirects[i] != NULL)
			{
				printf("redir = %s\n", cmd->redirects[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}

int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;
	
	cmd = NULL;
	//tokenizer
	line_lst = parser(line);
	// show_t_list(line_lst, line);
	line_lst = remove_whitespace_list(line_lst);
	// show_t_list(line_lst, line);
	if (!syntax_check(line_lst))
	{
		// printf("syntax check gaat verder\n");
		// show_t_list(line_lst, line);
		line_lst = variable_expand(line_lst, envp);
		// show_t_list(line_lst, line);
		cmd = alloc_execute_list(line_lst);
		cmd = acco(cmd);	
		// show(cmd);
		// execute_cmd_list(cmd, &data);
		// free
		delete_t_list(line_lst);
		delete_t_exec(cmd);
	}
	else
	{
		printf("syntax_check false\n"); //free line_lst
		// exit(1);
	}
	// if (cmd != NULL)
	// 	free(cmd);
	
	return (1);
}

void	ft_atexit(void)
{
	system("leaks -q minishell");
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
	atexit(ft_atexit);
	while (1)
	{	
		// if (argc != 1)
		// 	exit(1); 1?
		// signal(SIGINT, redirect_signal);
		line_reader(&line, "minishell$ ");
		if (!ft_strncmp(line, "exit", 5))
		{
			// free(line);
			exit(1);
		}
		shell(line, envp);
		free(line);
	}
	return (0);
}