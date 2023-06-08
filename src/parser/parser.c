/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/08 11:45:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>

t_node_type	get_prev_type(t_line_lst *node)
{
	t_node_type	type;

	type = e_start;
	while (node != NULL)
	{
		type = node->type;
		if (node->type == e_wspace && node->prev != NULL)
		{
			node = node->prev;
			type = node->type;
			node = node->next;
		}
		node = node->next;
	}
	return (type);
}

int	pars_specials(int i, char *line, int state, t_line_lst	**line_lst)
{
	if (line[i])
	{
		if (line[i] == '|')
			i += pipe_c(line_lst, state);
		else if (line[i] == '<')
			i += delim_c(line_lst, &line[i], state);
		else if (line[i] == '>')
			i += redirect_c(line_lst, &line[i], state);
		else if (line[i] == '$')
			i += dollar_c(line_lst, &line[i], state);
		else if (ft_isspace(line[i]))
			i += space_c(line_lst, state);
		else if (ft_isspace(line[i]))
			i += space_c(line_lst, state);
		else
			i++;
	}
	return (i);
}

t_line_lst	*parser(char *line)
{
	int			i;
	int			state;
	t_line_lst	*line_lst;

	i = 0;
	state = 0;
	line_lst = NULL;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
			i += word_case(&line_lst, line + i, state);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			state = quotes(&line_lst, line[i], state, state);
			i++;
		}
		else
			i = pars_specials(i, line, state, &line_lst);
	}
	return (line_lst);
}

t_line_lst	*remove_whitespace_list(t_line_lst *line_lst)
{
	t_line_lst	*new_head;
	t_line_lst	*prev;
	t_line_lst	*next;

	while (line_lst != NULL)
	{
		next = line_lst->next;
		if (line_lst->type == e_wspace && line_lst->state == 0)
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

t_line_lst	*word_list(t_line_lst *line)
{
	t_line_lst	*temp;
	char		*str;
	int			i;

	i = 0;
	temp = line;
	str = "";
	while (temp != NULL && temp->state > 0)
	{
		str = ft_strjoin(str, temp->value);
		temp = temp->next;
		free(temp);
		i++;
	}
	line->value = NULL;
	line->value = ft_strdup(str);
	line->next = temp;
	return (line);
}
