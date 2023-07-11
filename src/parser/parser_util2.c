/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/11 19:47:59 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

//printf("cmd= %d red = %d\n", node->count_cmd, node->count_red);
t_execute	*c_node_exec(t_line_lst *head)
{
	t_execute	*node;

	node = ft_malloc(sizeof(t_execute));
	node->count_red = count_redirectss(head);
	node->count_cmd = count_commands(head) - node->count_red;
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
		if (!ft_strcmp(head->value, "|") && head->type == e_pipe)
			break ;
		if ((!specials(head, 1) && head->type != e_file) || \
		(!ft_strcmp(head->value, "|") && head->type == e_word))
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

	tem = bad_functions(tem);
	while (tem != NULL)
	{
		new_node = c_node_exec(tem);
		while (tem != NULL && (ft_strcmp(tem->value, "|") || \
		tem->type == e_word))
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
