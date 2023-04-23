/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/14 15:17:05 by dyeboa        ########   odam.nl         */
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
	int i;
	int k;
	t_execute *cmdlist = NULL;
 	t_execute *last = NULL;
	char *temp;
	while (head != NULL)
	{
		k = 0;
		i = count_commands(head);
		t_execute *new_node = malloc(sizeof(t_execute));
        new_node->cmd = malloc(sizeof(char *) * (i + 1));
        new_node->next = NULL;
		while (head != NULL && k < i)
		{
			if (head->state > 0)
			{
				temp = make_string(head);
				if (temp[0] == '\"')
					new_node->cmd[k] = ft_substr(temp, 1, ft_strlen(temp) - 2);
				while (head != NULL && head->state > 0)
					head = head->next;
			}
			else
			{
            	new_node->cmd[k] = ft_strdup(head->value);
				head = head->next;
			}
            // printf("new_node->cmd[%d] == %s\n", k, new_node->cmd[k]);
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

t_execute *acco(t_execute *cmds)
{
    int i;
    int ir;
    t_execute *new_node;
    t_execute *temp;

    new_node = malloc(sizeof(t_execute));
    ir = 0;
    temp = new_node;
    int ic;
    while (cmds != NULL)
    {
        i = 0;
        while (cmds->cmd[i])
        {
            if (!ft_strcmp(cmds->cmd[i], ">") || !ft_strcmp(cmds->cmd[i], ">>") || !ft_strcmp(cmds->cmd[i], "<") || !ft_strcmp(cmds->cmd[i], "<<"))
                ir++;
            i++;
        }
        i = i - ir;
        new_node->cmd = malloc(sizeof(char *) * (i + 1));
        new_node->redirects = malloc(sizeof(char *) * (ir * 2 + 1));
        i = 0;
        ic = 0;
        ir = 0;
        while (cmds->cmd[i] != NULL && cmds->cmd[ir] && cmds->cmd[ic])
        {
            if (!ft_strcmp(cmds->cmd[i], ">") || !ft_strcmp(cmds->cmd[i], ">>") || !ft_strcmp(cmds->cmd[i], "<") || !ft_strcmp(cmds->cmd[i], "<<"))
            {
                new_node->redirects[ir] = ft_strdup(cmds->cmd[i]);
                // printf("redir string[%d] = %s\n", ir, new_node->redirects[ir]);
                i++;
                ir++;
                new_node->redirects[ir] = ft_strdup(cmds->cmd[i]);
                // printf("redir string[%d] = %s\n", ir, new_node->redirects[ir]);
                ir++;
            }
            else
            {
                new_node->cmd[ic] = ft_strdup(cmds->cmd[i]);
                // printf("cmd string[%d] = %s\n", i, new_node->cmd[i]);
                ic++;
            }
            i++;
        }
        new_node->cmd[ic] = NULL;
        new_node->redirects[ir] = NULL;
        cmds = cmds->next;
        if (cmds != NULL)
        {
            new_node->next = malloc(sizeof(t_execute));
            new_node = new_node->next;
        }
    }
    return(temp);
}

void	show(t_execute *cmd)
{
	int i;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->cmd[i] != NULL)
		{
			printf("cmd[%d] = %s\n",i, cmd->cmd[i]);
			i++;
		}
		i = 0;
		while (cmd->redirects[i] != NULL)
		{
			printf("redir = %s\n", cmd->redirects[i]);
			i++;
		}
		cmd = cmd->next;
	}
}
int	shell(char *line, char **envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;
	int i;
	i = 0;
	line_lst = parser(line);
	// show_t_list(line_lst, line);
	line_lst = expander(line_lst);
	// show_t_list(line_lst, line);
	cmd = alloc_execute_list(line_lst);
	cmd = acco(cmd);
	show(cmd);
	
	executor_dcs(cmd, envp); //DCS
	// execute_cmd_list(cmd, &data);
	// if (!is_valid_grammer(line_lst))
	// 	return (1);
	// test_lists(line_lst, envp);
	i++;
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
		if (!ft_strncmp(line, "exit", 5))
			exit(1);
		shell(line, envp);
	}
	return (0);
}
