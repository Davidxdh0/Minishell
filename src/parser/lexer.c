/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 20:43:01 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 21:08:51 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	ft_isspecial(char chr)
{
	return (ft_isspace(chr) || chr == '$' || chr == '<' || chr == '>' || \
	chr == '\n' \
	|| chr == '|' || chr == '\0' || chr == '\t' || chr == '\'' || chr == '\"');
}

int	ft_isspecials(char chr)
{
	return (ft_isspace(chr) || chr == '<' || chr == '>' || chr == '\n' \
	|| chr == '|' || chr == '\0' || \
	chr == '\t' || chr == '\'' || chr == '\"');
}

int	word_case(t_line_lst **line_lst, char *line, int state, int i)
{
	int			len;
	char		*substr;
	t_node_type	l;

	l = get_prev_type(*line_lst);
	if (!ft_isspecial(line[i]))
	{
		len = 0;
		while (!ft_isspecial(line[i + len]))
			len++;
		substr = ft_substr(line, i, len);
		if (l == e_start || l == e_pipe || l == e_file)
			add_at_end_of_list(line_lst, e_cmd, substr, state);
		if (l == e_cmd || l == e_word || l == e_quote || \
		l == e_var || l == e_dquote || l == e_wspace)
			add_at_end_of_list(line_lst, e_word, substr, state);
		if (l == e_redirect_i || l == e_redirect_o || l == e_append \
			|| l == e_delimiter)
			add_at_end_of_list(line_lst, e_file, substr, state);
		i += len;
		free(substr);
	}
	return (i);
}

int	quotes(t_line_lst **line_lst, char c, int state, int flag)
{
	flag = state;
	if (c == '\'')
	{
		if (state == 0)
			state = 1;
		else if (state == 1)
			state = 0;
	}
	else
	{
		if (state == 0)
			state = 2;
		else if (state == 2)
			state = 0;
	}
	if (flag > 0 && c == '\'')
		add_at_end_of_list(line_lst, e_quote, "\'", flag);
	else if ((flag > 0 && c == '\"'))
		add_at_end_of_list(line_lst, e_quote, "\"", flag);
	else if (c == '\'')
		add_at_end_of_list(line_lst, e_quote, "\'", state);
	else
		add_at_end_of_list(line_lst, e_quote, "\"", state);
	return (state);
}
