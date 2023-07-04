/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 21:28:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/04 15:46:37 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	populate_red(t_execute *node, t_line_lst *head, int count_red)
{
	while (head != NULL && head->type != e_cmd)
	{
		if (!ft_strcmp(head->value, "|") && head->state == 0)
			break ;
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
	count_red++;
}

int	count_redirectss(t_line_lst *head)
{
	int			i;
	t_line_lst	*temp;

	i = 0;
	temp = head;
	while (temp != NULL && ft_strcmp(temp->value, "|"))
	{
		if (specials(temp, 1) && ft_strcmp(temp->value, "|"))
		{
			i++;
			if (ft_strcmp(temp->next->value, "|"))
				i++;
		}
		temp = temp->next;
	}
	return (i);
}

void	free_single_node(t_line_lst *temp)
{
	free(temp->value);
	free(temp);
}
