/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/13 18:02:13 by dyeboa        ########   odam.nl         */
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
		node = node->next;
	}
	return (type);
}

t_line_lst	*parser(char *line)
{
	int				i;
	t_line_lst		*line_lst;
	int				state;

	state = normal;
	i = 0;
	line_lst = NULL;
	printf("%s\n", line);
	while (line[i])
	{
		printf("%c\n", line[i]);
		if (!ft_isspecial(line[i]))
			i += word_case(&line_lst, line + i, &state);
		else if (line[i] == '\"')
			i += quotes(line_lst, line[i], &state);
		else if (line[i] == '\'')
			i += pipe_case(&line_lst);
		else if (line[i] == '|')
			i += pipe_case(&line_lst);
		else if (line[i] == '<')
			i += less_than_case(&line_lst, &line[i]);
		else if (line[i] == '>')
			i += greater_than_case(&line_lst, &line[i]);
		else if (line[i] == '$')
			i += dolar_sign_case(&line_lst, &line[i]);
		else if (ft_isspace(line[i]))
			i += space_case(&line_lst);
		else
			i++;
	}
	return (line_lst);
}
