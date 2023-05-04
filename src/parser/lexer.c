/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 15:20:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/03 15:34:18 by dyeboa        ########   odam.nl         */                                                           
/* ************************************************************************** */

#include "../main/main.h"

int	ft_isspecial(char chr)
{
	return(ft_isspace(chr) || chr == '$' || chr ==  '<' || chr == '>' || chr == '\n' \
		|| chr == '|' || chr == '\0' ||  chr == '\'' || chr == '\"');
}

int	word_case(t_line_lst **line_lst, char *line, int state)
{
	int		i;
	int		len;
	note_type	last;

	i = 0;
	// printf("sd\n");
	last = get_last_type(*line_lst);
	// printf("last = %d", last);
	if (!ft_isspecial(line[i]))
	{
		len = 0;
		while (!ft_isspecial(line[i + len]))
		{
			// printf("character = %c\n", line[i + len]);
			len++;
		}
		// printf("state = %d", (int)state);
		if (last == e_start || last == e_pipe || last == e_file)
			add_at_end_of_list(line_lst, e_cmd, ft_substr(line, i, len), state);
		if (last == e_cmd || last == e_word || last == e_delimiter || last == e_quote || last == e_var || last == e_dquote || last == e_whitespace )
			add_at_end_of_list(line_lst, e_word, ft_substr(line, i, len), state);
		if (last == e_redirect_i || last == e_redirect_o || last == e_append)
			add_at_end_of_list(line_lst, e_file, ft_substr(line, i, len), state);
		i += len;
	}
	return (i);
}

int	quotes(t_line_lst *line_lst, char c, int state)
{
	int flag;

	flag = state;
	// printf("c = %c\n", c);
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
		add_at_end_of_list(&line_lst, e_quote, "\'", flag);
	else if ((flag > 0 && c == '\"'))
		add_at_end_of_list(&line_lst, e_quote, "\"", flag);
	else if (c == '\'')
		add_at_end_of_list(&line_lst, e_quote, "\'", state);
	else
		add_at_end_of_list(&line_lst, e_quote, "\"", state);
	return (state);
}