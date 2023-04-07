/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/07 18:12:24 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp

int	ft_isspecial(char chr)
{
	return(ft_isspace(chr) || chr == '$' || chr ==  '<' || chr == '>' || chr == '\n' \
		|| chr == '|' || chr == '\0' ||  chr == '\'' || chr == '\"');
}

// int		is_word(t_line_lst **line_lst, char *line)
// {
// 	int i;

// 	int i = 0;
// 	int len = 0;
// 	while (!ft_isspecial(line[i]))
// 	{
// 		i++;
// 	}
// 	return (0);
// }

int	word_case(t_line_lst **line_lst, char *line, enum enum_state *state)
{
	int		i;
	int		len;
	note_type	last;

	i = 0;
	last = get_last_type(*line_lst);
	if (!ft_isspecial(line[i]))
	{
		len = 0;
		while (!ft_isspecial(line[i + len]))
		{
			printf("character = %c\n", line[i + len]);
			len++;
		}
		if (last == e_start || last == e_pipe)
			add_at_end_of_list(line_lst, e_cmd, ft_substr(line, i, len), *state);
		if (last == e_cmd || last == e_word || last == e_delimiter || last == e_quote || last == e_dquote)
			add_at_end_of_list(line_lst, e_word, ft_substr(line, i, len), *state);
		if (last == e_redirect_i || last == e_redirect_o || last == e_append)
			add_at_end_of_list(line_lst, e_file, ft_substr(line, i, len), *state);
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

int	quotes(t_line_lst *line_lst, char c, enum enum_state *state)
{
	// int i = 0;
	// // int j = 0;
	// int dquote = 0;
	// int quote = 0;
	char chr  = c;
	if (chr == 's')
		return (1);
	// printf("s %s\n", line_lst->state);
	// printf("%s\n", line_lst->value);
	add_at_end_of_list(&line_lst, e_quote, "\"", *state);
	// if (c == '\'')
	// 	if (quote == 0)
	// 		quote = 1; //open
	// 	else
	// 		quote = 0; // closed
	// else if (c == '\"')
	// {
	// 	if (dquote == 0)
	// 	{
	// 		dquote = 1;
	// 	}
	// 	else
	// 	{
	// 		dquote = 0; // closed
	// 	}
	// }
	// i++;
	return (1);
}

t_line_lst	*parser(char *line)
{
	int				i;
	t_line_lst		*line_lst;
	enum enum_state	state;

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
