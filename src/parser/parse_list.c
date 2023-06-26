/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 18:01:14 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 21:29:23 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	count_commands(t_line_lst *head)
{
	int			i;
	t_line_lst	*temp;

	temp = head;
	i = 0;
	while (temp != NULL && ft_strcmp(temp->value, "|"))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_line_lst	*remove_quotes(t_line_lst *ls, t_line_lst *nh, t_line_lst *prev)
{
	t_line_lst	*next;

	while (ls != NULL)
	{
		next = ls->next;
		if (((((ls->type == e_quote && ls->state == 2)) && \
			(ls->state == 2 && ft_strcmp(ls->value, "'"))) || ((ls->type \
			== e_quote && ls->state == 1) && ft_strcmp(ls->value, "\""))))
		{
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			free(ls->value);
			free(ls);
		}
		else
		{
			if (nh == NULL)
				nh = ls;
			prev = ls;
		}
		ls = next;
	}
	return (nh);
}

int	specials(t_line_lst *lst, int i)
{	
	if (i >= 1 && lst->state == 0)
	{
		if (lst->type == e_delimiter)
			return (1);
		if (lst->type == e_redirect_i)
			return (1);
		if (lst->type == e_redirect_o)
			return (1);
		if (lst->type == e_append)
			return (1);
		if (lst->type == e_pipe)
			return (1);
	}
	if (i >= 2 && lst->state == 0)
	{
		if (lst->next->type == e_delimiter || lst->next->type == e_redirect_i)
			return (1);
		if (lst->next->type == e_redirect_o || lst->next->type == e_append)
			return (1);
		if (lst->next->type == e_pipe)
			return (1);
	}
	return (0);
}

t_line_lst	*combine_values(t_line_lst *list, t_line_lst *cur, t_line_lst *next)
{
	t_line_lst	*temp;

	while (cur != NULL)
	{
		if ((cur->state != 0 || cur->type != e_wspace) && (!specials(cur, 1)))
		{
			next = cur->next;
			while (next != NULL && (next->state != 0 || \
			next->type != e_wspace) && (!specials(cur, 2)))
			{
				cur->value = combine_thestring(cur->value, next->value);
				temp = next;
				next = next->next;
				free_single_node(temp);
			}
			cur->type = e_word;
			cur->next = next;
		}
		cur = cur->next;
	}
	return (list);
}

t_line_lst	*combine_quotes(t_line_lst *list)
{
	t_line_lst	*cur;
	t_line_lst	*next_node;

	cur = list;
	while (cur != NULL)
	{
		if (cur->state != 0 && cur->type == e_quote)
		{
			if (cur->next != NULL)
			{
				if (((cur->next->value[0] == '"' && cur->state == 2) || \
					((cur->next->value[0] == '\'' && cur->state == 1))) \
					&& check_combine(cur))
				{
					next_node = cur->next;
					free(cur->value);
					cur->value = ft_strdup("");
					cur->type = e_var;
					delete_node(next_node);
				}
			}
		}
		cur = cur->next;
	}
	return (list);
}
