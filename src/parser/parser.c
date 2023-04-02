/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/02 12:40:29 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp

int		is_word(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (ft_isdigit(c))
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

int	word_case(t_line_lst **line_lst, char *line)
{
	int		i;
	int		len;
	note_type	last;

	i = 0;
	last = get_last_type(*line_lst);
	if (is_word(line[i]))
	{
		len = 0;
		while (is_word(line[i + len]))
		{
			// printf("character = %c\n", line[i + len]);
			len++;
		}
		if (last == e_start || last == e_pipe)
			add_at_end_of_list(line_lst, e_cmd, ft_substr(line, i, len));
		if (last == e_cmd || last == e_word || last == e_delimiter)
			add_at_end_of_list(line_lst, e_word, ft_substr(line, i, len));
		if (last == e_redirect_i || last == e_redirect_o || last == e_append)
			add_at_end_of_list(line_lst, e_file, ft_substr(line, i, len));
		i += len;
	}
	return (i);
}

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
	int			i;
	t_line_lst	*line_lst;

	i = 0;
	line_lst = NULL;
	printf("%s\n", line);
	while (line[i])
	{
		// printf("%c=", line[i]);
		// printf("%d\n", i);
		if (line[i] == '|')
			i += pipe_case(&line_lst);
		else if (line[i] == '<')
			i += less_than_case(&line_lst, &line[i]);
		else if (line[i] == '>')
			i += greater_than_case(&line_lst, &line[i]);
		else if (line[i] == '$')
			i += dolar_sign_case(&line_lst, &line[i]);
		else if (is_word(line[i]))
			i += word_case(&line_lst, &line[i]);
		else if (line[i] == ' ')
		{
			while(line[i] == 32)
			{
				add_at_end_of_list(&line_lst, e_whitespace, " ");
				printf("character = '%c' at %d\n", line[i], i);
				i++;
			}
		}
		else
			i++;
	}
	return (line_lst);
}
