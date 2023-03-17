/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/17 15:26:24 by dyeboa        ########   odam.nl         */
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
			len++;
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

t_line_lst	*fil_list(char *line)
{
	t_line_lst	*head;
	note_type	last_type;
	int			i;
	int			len;

	i = 0;
	head = NULL;
	//line = ft_strtrim(line, " ");
	while (line[i])
	{
		last_type = get_last_type(head);

		if (line[i] == '|')
			add_at_end_of_list(&head, e_pipe, "|");
		else if (line[i] == '"')
			add_at_end_of_list(&head, e_dquote, "\"");
		else if (line[i] == ' ')
			add_at_end_of_list(&head, e_whitespace, " ");
		else if (line[i] == '<')
		{
			i++; 
			if (line[i] != '<')
			{
				add_at_end_of_list(&head, e_redirect_i, "<");
				continue;
			}
			add_at_end_of_list(&head, e_delimiter, "<<");
		}	
		else if (line[i] == '>')
		{
			i++;
			if (line[i] != '>')
			{
				add_at_end_of_list(&head, e_redirect_o, ">");
				continue;
			}	
			add_at_end_of_list(&head, e_append, ">>");
		}
		else if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				add_at_end_of_list(&head, e_var, "$?");
				i++;
				continue;
			}
			if (line[i] == '$')
			{
				add_at_end_of_list(&head, e_var, "$$");
				i++;
				continue;
			}	
			len = 0;
			while (line[i + len] && ft_isascii(line[i + len]) && line[i + len] != ' ')
				len++;
			add_at_end_of_list(&head, e_var, ft_substr(line, i, len));
			i += len - 1;
		}
		else if (ft_isascii(line[i]) && line[i] != ' ')
		{
			len = 0;
			while (line[i + len] && ft_isascii(line[i + len]) && line[i + len] != ' ')
				len++;
			if (last_type == e_start || last_type == e_pipe)
				add_at_end_of_list(&head, e_word, ft_substr(line, i, len));
			if (last_type == e_cmd || last_type == e_word || last_type == e_delimiter ||  last_type == e_whitespace)
				add_at_end_of_list(&head, e_word, ft_substr(line, i, len));
			if (last_type == e_redirect_i || last_type == e_redirect_o || last_type == e_append)
				add_at_end_of_list(&head, e_file, ft_substr(line, i, len));
			if (line[i + len] != ' ')
				len++;
			i += len - 1;
		}
		i++;
	}
	return (head);
}

t_line_lst	*parser(char *line)
{
	int			i;
	t_line_lst	*line_lst;

	i = 0;
	line_lst = NULL;
	while (line[i] != '\0')
	{
		// printf("%c ", line[i]);
		// printf("%d", i);
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
		// else if (line[i] == ' ')
		// {
		// 	add_at_end_of_list(&line_lst, e_whitespace, " ");
		// 	i++;
		// }
		else
			i++;
	}
	return (line_lst);
}
