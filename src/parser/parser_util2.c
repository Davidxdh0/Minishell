/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/08 16:00:37 by dyeboa        ########   odam.nl         */
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

t_execute	*alloc_execute_list(t_line_lst *head)
{
	int			k;
	t_execute	*new_node;
	t_execute	*cmdlist;
	t_execute	*last;
	// char		*temp;

	cmdlist = NULL;
	last = NULL;
	while (head != NULL)
	{
		k = 0;
		new_node = malloc(sizeof(t_execute));
		new_node->count_cmd = count_commands(head);
		new_node->cmd = malloc(sizeof(char *) * (new_node->count_cmd + 1));
		new_node->redirects = NULL;
		new_node->next = NULL;
		while (head != NULL && k < new_node->count_cmd)
		{
			if (head->state > 0)
			{
				new_node->cmd[k] = make_string(head);
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
		if (head != NULL)
			head = head->next;
	}
	return (cmdlist);
}

// t_execute	*alloc_execute_list(t_line_lst *head)
// {
// 	t_execute	*cmdlist;
// 	t_execute	*last;
// 	t_execute	*new_node;

// 	cmdlist = NULL;
// 	last = NULL;
// 	while (head != NULL)
// 	{
// 		new_node = create_execute_nodes(head);
// 		fill_command_arrays(new_node, &head);
// 		if (last == NULL)
// 			cmdlist = new_node;
// 		else
// 			last->next = new_node;
// 		last = new_node;
// 		if (head != NULL)
// 			head = head->next;
// 	}
// 	return (cmdlist);
// }

t_execute	*create_execute_nodes(t_line_lst *head)
{
	t_execute	*new_node;

	new_node = malloc(sizeof(t_execute));
	new_node->count_cmd = count_commands(head);
	new_node->cmd = malloc(sizeof(char *) * (new_node->count_cmd + 1));
	new_node->redirects = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	fill_command_arrays(t_execute *new_node, t_line_lst **head_ptr)
{
	int			k;
	t_line_lst	*head;

	k = 0;
	head = *head_ptr;
	while (head != NULL && k < new_node->count_cmd)
	{
		if (head->state > 0)
		{
			new_node->cmd[k] = make_string(head);
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
	*head_ptr = head;
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
