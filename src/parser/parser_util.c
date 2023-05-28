/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_util.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:33:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/28 21:33:59 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_execute *acco(t_execute *cmds)
{
    t_execute *new_list;
    t_execute *current_node;
	t_execute *head;
    int num_redirects;
    int num_commands;

	head = cmds;
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
	delete_t_exec(head);
    return (new_list);
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

t_execute *create_new_node(int num_commands, int num_redirects)
{
    t_execute *new_node = malloc(sizeof(t_execute));
    new_node->cmd = malloc(sizeof(char *) * (num_commands + 1));
    new_node->redirects = malloc(sizeof(char *) * (num_redirects * 2 + 1));
    new_node->next = NULL;
    return (new_node);
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
int ft_arrlen(char **arr)
{
    int i = 0;
    while (arr[i] != NULL)
        i++;
    return (i);
}