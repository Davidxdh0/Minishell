/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/13 15:39:12 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	**make_redirects(t_line_lst *line_l)
{
	char		**tempstring;
	t_line_lst	*temp;
	int			i;

	i = 0;
	temp = line_l;
	while (temp != NULL && ft_strcmp(line_l->value, "|"))
	{
		if (ft_isredirect(line_l->value) || ft_isredirect(line_l->prev->value))
			i++;
		temp = temp->next;
	}
	tempstring = malloc(sizeof(char **) * i + 1);
	temp = line_l;
	i = 0;
	while (line_l != NULL && ft_strncmp(line_l->value, "|", 1))
	{
		if (ft_isredirect(line_l->value))
			tempstring[i] = ft_strdup(line_l->value);
		else if (ft_isredirect(line_l->prev->value))
			tempstring[i] = ft_strdup(line_l->value);
		i++;
		temp = temp->next;
	}
	return (tempstring);
}

t_execute	*c_node_exec(t_line_lst *head)
{
	t_execute	*new_node;

	new_node = malloc(sizeof(t_execute));
	new_node->count_cmd = count_commands(head);
	new_node->cmd = malloc(sizeof(char *) * (new_node->count_cmd + 1));
	new_node->redirects = NULL;
	new_node->next = NULL;
	return (new_node);
}

char	*make_string(t_line_lst *line_lst)
{
	char	*tempstring;

	tempstring = NULL;
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
	return (tempstring);
}

void	populate_cmd(t_execute *new_node, t_line_lst **head_ref, int count_cmd)
{
	int	k;

	k = 0;
	while (*head_ref != NULL && k < count_cmd)
	{
		if ((*head_ref)->state > 0)
		{
			new_node->cmd[k] = make_string(*head_ref);
			while (*head_ref != NULL && (*head_ref)->state > 0)
				*head_ref = (*head_ref)->next;
		}
		else
		{
			new_node->cmd[k] = ft_strdup((*head_ref)->value);
			*head_ref = (*head_ref)->next;
		}
		k++;
	}
	new_node->cmd[k] = NULL;
}

t_execute	*alloc_execute_list(t_line_lst *head)
{
	t_execute	*new_node;
	t_execute	*cmdlist;
	t_execute	*last;

	cmdlist = NULL;
	last = NULL;
	while (head != NULL)
	{
		new_node = c_node_exec(head);
		populate_cmd(new_node, &head, new_node->count_cmd);
		if (last == NULL)
			cmdlist = new_node;
		else
			last->next = new_node;
		last = new_node;
		if (head != NULL)
			head = head->next;
	}
	return (cmdlist);
}
