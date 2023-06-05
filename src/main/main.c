/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/05 15:21:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_isredirect(char *str)
{
	if (ft_strcmp(str, ">") || ft_strcmp(str, ">>") || ft_strcmp(str, "<") || ft_strcmp(str, "<<"))
		return (1);
	return (0);
}
int		count_commands(t_line_lst *head)
{
	int i;

	t_line_lst *temp;
	temp = head;
	i = 0;
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
			printf("dfxd");
		if (temp != NULL)
			temp = temp->next;
		i++;
	}
	return (i);
}

void	show(t_execute *cmd)
{
	int i;

	printf("\n");
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
		printf("\n");
	}
}

t_line_lst *remove_quotes(t_line_lst *line_lst)
{
    t_line_lst *new_head = NULL;
    t_line_lst *prev = NULL;

    while (line_lst != NULL)
    {
        t_line_lst *next = line_lst->next;
        if ((line_lst->type == e_quote && line_lst->state == 1) || (line_lst->type == e_quote && line_lst->state == 2))
        {
            if (prev != NULL)
                prev->next = next;
            if (next != NULL)
                next->prev = prev;
            free(line_lst->value);
            free(line_lst);
        }
        else
        {
            if (new_head == NULL)
                new_head = line_lst;
            prev = line_lst;
        }
        line_lst = next;
    }
    return (new_head);
}
t_line_lst	*combine_values(t_line_lst *list)
{
    t_line_lst	*current;
	t_line_lst	*nextNode;
	char		*new_value;
	t_line_lst 	*temp;
	
	current = list;
    while (current != NULL)
    {
        if (current->state != 0 || current->type != e_whitespace)
        {
            nextNode = current->next;
            while (nextNode != NULL && (nextNode->state != 0 || nextNode->type != e_whitespace))
            {
                current->len += nextNode->len;
				new_value = ft_strdup(current->value);
                ft_strlcat(new_value, nextNode->value, current->len + 1);
                free(current->value);
                current->value = new_value;
                temp = nextNode;
                nextNode = nextNode->next;
                free(temp);
            }
            current->next = nextNode;
        }
        current = current->next;
    }
    return (list);
}

t_line_lst	*combine_quotes(t_line_lst *list)
{
    t_line_lst	*current;

	current = list;
    while (current != NULL)
    {
        if (current->state != 0 && current->type == e_quote)
        {
			if (current->next != NULL)
			{
				if ((current->next->type == e_quote && current->next->state == 2) \
				|| (current->next->type == e_quote && current->next->state == 1))
				{
					current->next->value = ft_strdup("");
					current->next->type = e_var;
					current->next->state = 0;
					if (current->next->next != NULL)
						delete_node(current);
				}
			}
        }
        current = current->next;
    }
    return (list);
}	

int	shell(char *line, t_envp *envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;
	
	cmd = NULL;
	line_lst = parser(line);
	// show_t_list(line_lst, line);
	if (syntax_count_quotes(line_lst))
		return (0);
	line_lst = variable_expand(line_lst, envp);
	show_t_list(line_lst, line);
	line_lst = combine_quotes(line_lst);
	show_t_list(line_lst, line);
	line_lst = remove_quotes(line_lst);
	show_t_list(line_lst, line);
	line_lst = combine_values(line_lst);
	show_t_list(line_lst, line);
	line_lst = remove_whitespace_list(line_lst);
	// show_t_list(line_lst, line);
	if (!syntax_check(line_lst))
	{
		// show_t_list(line_lst, line);
		cmd = alloc_execute_list(line_lst);
		cmd = acco(cmd);	
		show(cmd);
		// executor_dcs(cmd, envp); //DCS
		delete_t_exec(cmd);
		// 255, exit shit??
	}
	else
	{
		g_exitcode = 258;//printf("Syntax error doesn't get executed -> exitcode = ?\n");
	}
	if (line_lst != NULL)
		delete_t_list(line_lst);
	return (1);
}

void	ft_atexit(void)
{
	system("leaks -q minishell");
}


int	main(int argc, char *argv[], char **original_envp)
{
	static char	*line; //does this need to be static??
	t_envp		*envp;
	signal(SIGINT, signal_int);   // Handle Ctrl-C
	// signal(SIGQUIT, signal_handler);  // Handle Ctrl-'/'
	// 
	// if (argc != 1)
	// 	malloc met exit code + tekst perror("executable: " )
	signal(SIGQUIT, signal_bs); 
	envp = copy_envp(original_envp);
	g_exitcode = 0;
	
	while (1)
	{	
		// if (argc != 1)
		// 	exit(1); 1?
		disable_ctrl_c_display();
		line_reader(&line, "minishell$ ");
		if (line != NULL)
		{
			if (!ft_strncmp(line, "exit", 4) || !ft_strncmp(line, "make", 4))
				free(line);
			enable_ctrl_c_display();
			shell(line, envp);
			free(line);
		}
	}
	// atexit(ft_atexit);
	return (0);
}
