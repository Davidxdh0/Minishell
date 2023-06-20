/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 21:28:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/20 19:37:00 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	populate_red(t_execute *node, t_line_lst *head, int count_red)
{
	while (head != NULL && head->type != e_cmd)
	{
		if (!ft_strcmp(head->value, "|") && head->state == 0)
			break ;
		while (head != NULL && specials(head, 1))
		{
			node->redirects[node->cr] = ft_strdup(head->value);
			node->cr++;
			head = head->next;
			node->redirects[node->cr] = ft_strdup(head->value);
			node->cr++;
			node->count_red -= 2;
		}
		head = head->next;
	}
	node->redirects[node->cr] = NULL;
	count_red++;
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
