/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 19:09:34 by dyeboa        ########   odam.nl         */
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
	tempstring = ft_malloc(sizeof(char **) * i + 1);
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

// printf("countcmd = %d count red = %d\n", node->count_cmd, node->count_red);
t_execute	*c_node_exec(t_line_lst *head)
{
	t_execute	*node;

	node = ft_malloc(sizeof(t_execute));
	node->count_cmd = count_commands(head);
	node->count_red = count_redirectss(head);
	node->ck = 0;
	node->cr = 0;
	if (node->count_cmd > 0)
		node->cmd = ft_malloc(sizeof(char *) * (node->count_cmd + 1));
	else
		node->cmd = NULL;
	if (node->count_red > 0)
		node->redirects = ft_malloc(sizeof(char *) * (node->count_red + 1));
	else
		node->redirects = NULL;
	node->heredoc_name = NULL;
	node->next = NULL;
	node->prev = NULL;
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
			free(tempstring);
			tempstring = temp;
		}
		line_lst = line_lst->next;
	}
	return (tempstring);
}

// printf("value = %s en k = %d count_cmd = %d\n", head->value, k, count_cmd);
void	populate_cmd(t_execute *node, t_line_lst *head, int count_cmd, int k)
{
	while (head != NULL && k < count_cmd)
	{
		if (!ft_strcmp(head->value, "|") && head->state == 0)
			break ;
		if (head->state > 0 && (!specials(head, 1)) && head->type != e_file)
		{
			node->cmd[k] = make_string(head);
			while (head != NULL && head->state > 0)
				head = head->next;
			k++;
		}
		else if (!specials(head, 1) && head->type != e_file)
		{
			node->cmd[k] = ft_strdup(head->value);
			head = head->next;
			k++;
		}
		else
			head = head->next;
	}
	node->count_cmd -= k;
	node->cmd[k] = NULL;
}

t_execute	*alloc_execute_list(t_line_lst *tem, t_execute	*l, t_execute *lst)
{
	t_execute	*new_node;

	while (tem != NULL)
	{
		new_node = c_node_exec(tem);
		while (tem != NULL && (ft_strcmp(tem->value, "|") || tem->state != 0))
		{
			if (new_node->count_cmd > 0)
				populate_cmd(new_node, tem, new_node->count_cmd, 0);
			if (new_node->count_red > 0)
				populate_red(new_node, tem, new_node->count_red);
			tem = tem->next;
		}
		if (lst == NULL)
			l = new_node;
		else
			lst->next = new_node;
		lst = new_node;
		if (tem != NULL)
			tem = tem->next;
	}
	return (l);
}
