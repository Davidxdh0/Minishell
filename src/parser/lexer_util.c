/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 14:55:53 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/06 18:18:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	dollar_special_c(t_line_lst **line_lst, char next_char, int state)
{
	t_node_type	type;

	type = get_prev_type(*line_lst);
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

int	dollar_c(t_line_lst **line_lst, char *line, int state)
{
	int			len;
	char		*str;
	t_node_type	type;

	type = get_prev_type(*line_lst);
	if (type == e_start || type == e_pipe)
		type = e_cmd;
	else
		type = e_word;
	if (line[1] == '$')
		return (dollar_special_c(line_lst, '$', state));
	if (line[1] == '?')
		return (dollar_special_c(line_lst, '?', state));
	if (line[1] == ' ' || line[1] == '\0')
	{
		add_at_end_of_list(line_lst, type, "$", state);
		return (1);
	}
	len = 1;
	while (!ft_isspecial(line[len]))
		len++;
	str = ft_substr(line, 0, len);
	add_at_end_of_list(line_lst, e_var, str, state);
	free(str);
	return (len);
}
