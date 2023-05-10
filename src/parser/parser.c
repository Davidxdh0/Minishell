/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/10 16:28:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp

note_type	get_last_type(t_line_lst *node)
{
	note_type	type;
	type = e_start;

	while (node != NULL)
	{
		type = node->type;
		if (node->type == e_whitespace && node->prev != NULL)
		{
			node = node->prev;
			type = node->type;
			node = node->next;
		}
		node = node->next;
	}
	return (type);
}

t_line_lst	*parser(char *line)
{
	int				i;
	t_line_lst		*line_lst;
	int				state;

	state = 0;
	i = 0;
	line_lst = NULL;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
			i += word_case(&line_lst, line + i, state);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			state = quotes(line_lst, line[i], state);
			i++;
		}
		else if (line[i] == '|')
			i += pipe_case(&line_lst, state);
		else if (line[i] == '<')
			i += less_than_case(&line_lst, &line[i], state);
		else if (line[i] == '>')
			i += greater_than_case(&line_lst, &line[i], state);
		else if (line[i] == '$')
			i += dolar_sign_case(&line_lst, &line[i], state);
		else if (ft_isspace(line[i]))
			i += space_case(&line_lst, state);
		else
			i++;
	}
	return (line_lst);
}

