/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/31 18:53:21 by dyeboa        ########   odam.nl         */
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
			printf("dfd");
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
void combine_values(t_line_lst *list)
{
    if (list == NULL) {
        return;
    }
    t_line_lst *current = list;
    while (current != NULL) {
        if (current->state != 0) {
            t_line_lst *nextNode = current->next;
            while (nextNode != NULL && (nextNode->type != e_whitespace && nextNode->state == 0)) 
			{
                current->len += nextNode->len;
                current->value = realloc(current->value, (current->len + 1) * sizeof(char));
                strcat(current->value, nextNode->value);
                t_line_lst *temp = nextNode;
                nextNode = nextNode->next;
                free(temp);
            }

            if (nextNode != NULL) {
                current->next = nextNode;
            } else {
                current->next = NULL;
            }
        }
        current = current->next;
    }
}
	

int	shell(char *line, char **original_envp, t_envp *envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;
	
	cmd = NULL;
	//tokenizer
	line_lst = parser(line);
	// show_t_list(line_lst, line);
	line_lst = remove_quotes(line_lst);
	// show_t_list(line_lst, line);
	line_lst = variable_expand(line_lst, original_envp);
	// line_lst = variable_expand(line_lst, original_envp);
	combine_values(line_lst);
	// show_t_list(line_lst, line);
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
	}
	else
	{
		;//printf("Syntax error doesn't get executed -> exitcode = ?\n");
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

	if (!*original_envp)
		return (1); //error message?
	envp = copy_envp(original_envp);
	// if (!copy_envp(envp, original_envp))
	// 	ft_exit_error("Failed To Copy The ENVP\n", 2); //edit
	g_exitcode = 0;
	if (input_is_argv(argc, argv, &line))
		return (shell(line, original_envp, envp));
	while (1)
	{	
		// if (argc != 1)
		// 	exit(1); 1?
		// signal(SIGINT, redirect_signal);
		line_reader(&line, "minishell$ ");
		if (!ft_strncmp(line, "exit", 4) || !ft_strncmp(line, "make", 4))
		{
			free(line);
			// exit(1);
		}
		shell(line, original_envp, envp);
		free(line);
	}
	// atexit(ft_atexit);
	return (0);
}
