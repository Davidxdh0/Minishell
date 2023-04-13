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
		printf("state = %d", (int)state);
		if (last == e_start || last == e_pipe)
			add_at_end_of_list(line_lst, e_cmd, ft_substr(line, i, len), state);
		if (last == e_cmd || last == e_word || last == e_delimiter || last == e_quote || last == e_dquote)
			add_at_end_of_list(line_lst, e_word, ft_substr(line, i, len), state);
		if (last == e_redirect_i || last == e_redirect_o || last == e_append)
			add_at_end_of_list(line_lst, e_file, ft_substr(line, i, len), state);
		i += len;
	}
	return (i);
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
	state = 0;
	add_at_end_of_list(&line_lst, e_quote, "\"", state);
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