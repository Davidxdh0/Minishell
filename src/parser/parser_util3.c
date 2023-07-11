/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 21:28:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/11 19:40:54 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	popuplate_red_utl(t_execute **node, t_line_lst *head)
{
	(*node)->redirects[(*node)->cr] = ft_strdup(head->value);
	(*node)->cr++;
}

void	populate_red(t_execute *node, t_line_lst *head, int count_red)
{
	while (head != NULL && head->type != e_cmd)
	{
		if (!ft_strcmp(head->value, "|") && head->type == e_pipe)
			break ;
		if (head->type == e_file && count_red == 1)
			popuplate_red_utl(&node, head);
		while (head != NULL && specials(head, 1) && count_red > 0)
		{
			node->redirects[node->cr] = ft_strdup(head->value);
			node->cr++;
			head = head->next;
			node->count_red--;
			count_red--;
			if (node->count_red > 0)
			{
				node->redirects[node->cr] = ft_strdup(head->value);
				node->cr++;
				node->count_red--;
				count_red--;
			}
		}
		head = head->next;
	}
	node->redirects[node->cr] = NULL;
}

int	count_redirectss(t_line_lst *head)
{
	int			i;
	t_line_lst	*temp;
	int			flag;

	i = 0;
	flag = 0;
	temp = head;
	while (temp != NULL && temp->type != e_pipe)
	{
		if (specials(temp, 1) && temp->type != e_pipe)
		{
			i++;
			if (temp->next != NULL)
				if (temp->next->type != e_pipe)
					i++;
		}
		if (temp->type == e_file)
			flag = 1;
		temp = temp->next;
	}
	if (flag == 1 && i == 0)
		i = 1;
	return (i);
}

void	free_single_node(t_line_lst *temp)
{
	free(temp->value);
	free(temp);
}
