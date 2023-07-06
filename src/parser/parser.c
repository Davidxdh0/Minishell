/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/06 13:11:40 by dyeboa        ########   odam.nl         */
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
			i += word_case(&line_lst, line + i, state, 0);
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

t_line_lst	*rm_wspace(t_line_lst *l, t_line_lst *nh, t_line_lst *prev)
{
	t_line_lst	*next;

	while (l != NULL)
	{
		next = l->next;
		if ((l->type == e_wspace && l->state == 0) || !ft_strcmp(l->value, ""))
		{
			if (l->prev != NULL)
				l->prev->state = 0;
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			free(l->value);
			free(l);
		}
		else
		{
			if (nh == NULL)
				nh = l;
			prev = l;
		}
		l = next;
	}
	return (nh);
}
