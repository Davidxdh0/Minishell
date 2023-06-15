/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 18:01:14 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/15 22:14:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	count_commands(t_line_lst *head)
{
	int			i;
	t_line_lst	*temp;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		if (specials(temp, 1))
		{
			temp = temp->next;
			i--;
		}
		else if (temp->state > 0)
		{
			while (temp != NULL && temp->state > 0)
				temp = temp->next;
			i++;
			if (!temp)
				return (i);
		}
		if (temp != NULL)
			temp = temp->next;
		i++;
	}
	return (i);
}

t_line_lst	*remove_quotes(t_line_lst *list, t_line_lst *nh, t_line_lst *prev)
{
	t_line_lst	*next;

	while (list != NULL)
	{
		next = list->next;
		if ((((list->type == e_quote && list->state == 2)) && \
			(list->state == 2 && ft_strcmp(list->value, "'"))) || \
			(list->type == e_quote && list->state == 1))
		{
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			free(list->value);
			free(list);
		}
		else
		{
			if (nh == NULL)
				nh = list;
			prev = list;
		}
		list = next;
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
	char		*new_value;
	t_line_lst	*temp;

	new_value = NULL;
	while (cur != NULL)
	{
		if ((cur->state != 0 || cur->type != e_wspace) && (!specials(cur, 1)))
		{
			next = cur->next;
			while (next != NULL && (next->state != 0 || \
			next->type != e_wspace) && (!specials(cur, 2)))
			{
				new_value = combine_thestring(cur->value, next->value);
				cur->value = ft_strdup(new_value);
				temp = next;
				next = next->next;
				free(temp->value);
				free(temp);
				free(new_value);
			}
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
				if ((cur->next->type == e_quote && cur->next->state == 2) || \
				(cur->next->type == e_quote && cur->next->state == 1))
				{
					next_node = cur->next;
					free(cur->value);
					cur->value = ft_strdup("");
					cur->type = e_var;
					cur->state = 0;
					delete_node(next_node);
				}
			}
		}
		cur = cur->next;
	}
	return (list);
}
