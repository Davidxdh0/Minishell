/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specialchar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/01 21:09:10 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	pipe_case(t_line_lst **line_lst, int state)
{
	add_at_end_of_list(line_lst, e_pipe, "|", state);
	return (1);
}

int	space_case(t_line_lst **line_lst, int state)
{
	add_at_end_of_list(line_lst, e_whitespace, " ", state);
	return (1);
}

int	less_than_case(t_line_lst **line_lst, char *line, int state)
{
	if (line[1] == '<')
	{
		add_at_end_of_list(line_lst, e_delimiter, "<<", state);
		return (2);
	}
	add_at_end_of_list(line_lst, e_redirect_i, "<", state);
	return (1);
}

int	greater_than_case(t_line_lst **line_lst, char *line, int state)
{
	if (line[1] == '>')
	{
		add_at_end_of_list(line_lst, e_append, ">>", state);
		return (2);
	}
	add_at_end_of_list(line_lst, e_redirect_o, ">", state);
	return (1);
}

int	dolar_special_case(t_line_lst **line_lst, char next_char, int state)
{
	node_type	type;

	type = get_previous_type(*line_lst);
	if (type == e_start || type == e_pipe)
		type = e_cmd;
	else
		type = e_var;
	if (next_char == '$')
		add_at_end_of_list(line_lst, type, "$$", state);
	if (next_char == '?')
		add_at_end_of_list(line_lst, type, "$?", state);
	return (2);
}

int	dolar_sign_case(t_line_lst **line_lst, char *line, int state)
{
	int			len;
	node_type	type;

	type = get_previous_type(*line_lst);
	if (type == e_start || type == e_pipe)
		type = e_cmd;
	else
		type = e_word;
	if (line[1] == '$')
		return (dolar_special_case(line_lst, '$', state));
	if (line[1] == '?')
		return (dolar_special_case(line_lst, '?', state));
	if (line[1] == ' ' || line[1] == '\0')
	{
		add_at_end_of_list(line_lst, type, "$", state);
		return (1);
	}
	len = 1;
	while (!ft_isspecial(line[len]))
		len++;
	add_at_end_of_list(line_lst, e_var, ft_substr(line, 0, len), state);
	return (len);
}
