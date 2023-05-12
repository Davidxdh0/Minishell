/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:27:35 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/12 16:56:33 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int syntax_pipe(t_line_lst *line)
{
	if (line->prev == NULL || line->next == NULL || line->next->type == e_pipe)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	// printf("syntax_pipe pass\n");
	return (0);
}

int syntax_quotes(t_line_lst *line, note_type type)
{
	while (line)
	{
		line = line->next;
		if (!line || line->type == type)
			break ;
	}
	if (!line)
	{
		printf("Quotes are not balanced\n");
		return (1);
	}
	printf("quotes pass");
	return (0);
}
// }

int	syntax_redirects(t_line_lst *line)
{
	//  < file   of < $file 
	if (line->type == e_redirect_i)
	{
		printf("shfje");
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var || line->prev->type != e_word || line->next->type != e_quote)
		{
			printf("syntax_redirects\tfaalt");
			// exit(1);
			return (1);
		}
	}
	//  file > of  $file >
	if (line->type == e_redirect_o )
	{
		if (line->prev == NULL || line->prev->type != e_file || line->prev->type != e_var || line->prev->type != e_word || line->next->type != e_quote)
			return (1);
	}
	// >> append 
	if (line->type == e_append)
	{
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var || line->next->type != e_word || line->next->type != e_quote)
			return (1);
	}
	// << heredoc
	if (line->type == e_delimiter)
	{
		if (line->next == NULL || line->next->type != e_file || line->next->type != e_var || line->next->type != e_word || line->next->type != e_quote)
			return (1);
	}
	printf("syntax_redirects pass\n");
	return (0);
}

int	syntax_check(t_line_lst *line)
{
	t_line_lst *temp;

	temp = line;
	// pipes
	while(temp)
	{
		if (temp->type == e_pipe)
			syntax_pipe(temp);
		// quotes
		if (temp->type == e_quote || temp->type == e_dquote)
			syntax_quotes(temp, temp->type);//printf("quote\n");
		// redirects
		if (temp->type == e_redirect_i || temp->type == e_append || \
			temp->type == e_redirect_o || temp->type == e_delimiter )
			{
				if (syntax_redirects(line))
					printf("redirect fails\n");
			}
			
		temp = temp->next;
	}
	return (0);
}
