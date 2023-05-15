/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:27:35 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/15 12:30:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int syntax_pipe(t_line_lst *line)
{
	if (line->prev == NULL || line->next == NULL || line->next->type == e_pipe)
	{
		// printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	printf("syntax pipe pass\n");
	return (0);
}

int syntax_quotes(t_line_lst *line, note_type type)
{
	char *str;

	while (line)
	{
		line = line->next;
		if (!line || line->type == type)
			break ;
	}
	if (!line)
	{
		str = ft_strdup("minishell: Quotes are not balanced");
		write(2, str, ft_strlen(str));
		return (1);
	}
	return (0);
}
// }

int	syntax_redirects(t_line_lst *line)
{
	//  < file   of < $file 
	if (line->type == e_redirect_i)
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var || \
		line->prev->type != e_word || line->next->type != e_quote)
			return (1);
	//  file > of  $file >
	if (line->type == e_redirect_o )
		if (line->prev == NULL || line->prev->type != e_file || line->prev->type != e_var || \
		line->prev->type != e_word || line->next->type != e_quote)
			return (1);
	// >> append 
	if (line->type == e_append)
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var || \
		line->next->type != e_word || line->next->type != e_quote)
			return (1);
	// << heredoc
	if (line->type == e_delimiter)
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var \
		|| line->next->type != e_word || line->next->type != e_quote)
			return (1);
	printf("syntax_redirects pass\n");
	return (0);
}

int	syntax_check(t_line_lst *line)
{
	t_line_lst *temp;

	temp = line;
	while(temp)
	{
		// pipes
		if (temp->type == e_pipe)
			if (syntax_pipe(temp))
				return (perror_return("minishell: syntax error near unexpected token `|'", NULL));
		// quotes
		if (temp->type == e_quote || temp->type == e_dquote)
			if (syntax_quotes(temp, temp->type))
				return (0);
		// redirects
		if (temp->type == e_redirect_i || temp->type == e_append || \
			temp->type == e_redirect_o || temp->type == e_delimiter )
			{
				if (syntax_redirects(line))
					return (perror_return("minishell: syntax error near unexpected token `|'", NULL));
			}
		temp = temp->next;
	}
	printf("syntax check klopt");
	return (0);
}
