/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/10 16:18:59 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp

note_type	get_last_type(t_line_lst *node)
{
	note_type	type;
	type = e_start;

	while (node != NULL)
	{
		type = node->type;
		if (node->type == e_whitespace && node->prev != NULL)
		{
			node = node->prev;
			type = node->type;
			node = node->next;
		}
		node = node->next;
	}
	return (type);
}

t_line_lst	*parser(char *line)
{
	int				i;
	t_line_lst		*line_lst;
	int				state;

	state = 0;
	i = 0;
	line_lst = NULL;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
			i += word_case(&line_lst, line + i, state);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			state = quotes(line_lst, line[i], state);
			i++;
		}
		else if (line[i] == '|')
			i += pipe_case(&line_lst, state);
		else if (line[i] == '<')
			i += less_than_case(&line_lst, &line[i], state);
		else if (line[i] == '>')
			i += greater_than_case(&line_lst, &line[i], state);
		else if (line[i] == '$')
			i += dolar_sign_case(&line_lst, &line[i], state);
		else if (ft_isspace(line[i]))
			i += space_case(&line_lst, state);
		else
			i++;
	}
	return (line_lst);
}


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

// int syntax_quotes(t_line_lst *line)
// {

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
			;//printf("quote\n");
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