/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 18:01:14 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/11 14:46:18 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	count_commands(t_line_lst *head)
{
	int			i;
	t_line_lst	*temp;

	temp = head;
	i = 0;
	while (temp != NULL && ft_strncmp(temp->value, "|", 1))
	{
		if (temp->state > 0)
		{
			while (temp != NULL && temp->state > 0)
				temp = temp->next;
			i++;
			if (!temp)
				return (i);
		}
		if (!ft_isredirect(temp->value))
			printf("thisneverhappens");
		if (temp != NULL)
			temp = temp->next;
		i++;
	}
	return (i);
}

t_line_lst	*remove_quotes(t_line_lst *line_lst)
{
	t_line_lst	*new_head;
	t_line_lst	*prev;
	t_line_lst	*next;

	new_head = NULL;
	while (line_lst != NULL)
	{
		next = line_lst->next;
		if ((line_lst->type == e_quote && line_lst->state == 1) || (line_lst->type == e_quote && line_lst->state == 2))
		{
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			free(line_lst->value);
			free(line_lst);
		}
		else
		{
			if (new_head == NULL)
				new_head = line_lst;
			prev = line_lst;
		}
		line_lst = next;
	}
	return (new_head);
}

t_line_lst	*combine_values(t_line_lst *list)
{
	t_line_lst	*cur;
	t_line_lst	*next;
	char		*new_value;
	t_line_lst	*temp;

	new_value = NULL;
	cur = list;
	while (cur != NULL)
	{
		if (cur->state != 0 || cur->type != e_wspace)
		{
			next = cur->next;
			
			while (next != NULL && (next->state != 0 || next->type != e_wspace))
			{
				cur->len += next->len;
				new_value = malloc(sizeof(char *) * cur->len + 1);
				ft_strlcpy(new_value, cur->value, cur->len + next->len + 1);
				ft_strlcat(new_value, next->value, cur->len + next->len + 1);
				free(cur->value);
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
					cur->next = next_node->next;
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
