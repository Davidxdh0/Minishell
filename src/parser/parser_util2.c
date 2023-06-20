/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/20 18:37:43 by dyeboa        ########   odam.nl         */
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
	t_execute	*node;

	node = ft_malloc(sizeof(t_execute));
	node->count_cmd = count_commands(head);
	node->count_red = count_redirectss(head);
	if (node->count_cmd > 0)
		node->cmd = ft_malloc(sizeof(char *) * (node->count_cmd + 1));
	else
		node->cmd = NULL;
	if (node->count_red > 0)
		node->redirects = ft_malloc(sizeof(char *) * (node->count_red + 1));
	else
		node->redirects = NULL;
	node->next = NULL;
	node->prev = NULL;
	printf("cmd %d red %d\n", node->count_cmd, node->count_red);
	return (node);
}

char	*make_string(t_line_lst *line_lst)
{
	char	*tempstring;
	char	*temp;	

	tempstring = NULL;
	if (line_lst->value)
		tempstring = ft_strdup(line_lst->value);
	while (line_lst != NULL && (ft_strcmp(line_lst->value, "|") && \
		line_lst->state != 0))
	{
		while (line_lst->next != NULL && line_lst->next->state > 0)
		{
			line_lst = line_lst->next;
			temp = ft_strjoin(tempstring, line_lst->value);
			if (temp == NULL)
			{
				free(tempstring);
				return (NULL);
			}
			free(tempstring);
			tempstring = temp;
		}
		line_lst = line_lst->next;
	}
	return (tempstring);
}

void	populate_cmd(t_execute *new_node, t_line_lst *head_ref, int count_cmd)
{
	int	k;

	k = 0;
	while (head_ref != NULL && k < count_cmd)
	{
		if (!ft_strcmp(head_ref->value, "|") && head_ref->state == 0)
			break ;
		if (head_ref->state > 0 && (!specials(head_ref, 1)) && head_ref->type != e_file)
		{
			new_node->cmd[k] = make_string(head_ref);
			while (head_ref != NULL && head_ref->state > 0)
				head_ref = head_ref->next;
			new_node->count_cmd--;
			k++;
		}
		else if (!specials(head_ref, 1) && head_ref->type != e_file)
		{
			new_node->cmd[k] = ft_strdup(head_ref->value);
			head_ref = head_ref->next;
			new_node->count_cmd--;
			k++;
		}
		else
			head_ref = head_ref->next;
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
		while(head != NULL && ft_strcmp(head->value, "|") && head->state == 0)
		{
			if (new_node->count_cmd > 0)
				populate_cmd(new_node, head, new_node->count_cmd);
			if (new_node->count_red > 0)
				populate_red(new_node, head, new_node->count_red);
			head = head->next;
		}
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
