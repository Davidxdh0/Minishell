/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 21:28:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/18 19:42:51 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	populate_red(t_execute *new_node, t_line_lst **head_ref, int count_red)
{
	int	k;

	k = 0;
	while (*head_ref != NULL && k < count_red)
	{
		if (!ft_strcmp((*head_ref)->value, "|") && (*head_ref)->state == 0)
			break ;
		while (*head_ref != NULL && specials(*head_ref, 1) && k < count_red)
		{
			new_node->redirects[k] = ft_strdup((*head_ref)->value);
			k++;
			(*head_ref) = (*head_ref)->next;
			new_node->redirects[k] = ft_strdup((*head_ref)->value);
			k++;
		}
		(*head_ref) = (*head_ref)->next;
	}
	new_node->redirects[k] = NULL;
}

int	count_redirectss(t_line_lst *head)
{
	int	i;

	i = 0;
	while (head != NULL && ft_strcmp(head->value, "|"))
	{
		if (specials(head, 1) && ft_strcmp(head->value, "|"))
		{
			i++;
			i++;
		}
		head = head->next;
	}
	return (i);
}

void	signal_bs1(int sig)
{
	sig++;
}

void	free_single_node(t_line_lst *temp)
{
	free(temp->value);
	free(temp);
}
