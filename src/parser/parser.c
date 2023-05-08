/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/04 20:36:46 by dyeboa        ########   odam.nl         */
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
	// printf("lijn = %s\n", line);
	while (line[i])
	{
		// printf("c = %c\n", line[i]);
		if (!ft_isspecial(line[i]))
		{
			// printf("isnotspecial = %c\n", line[i]);
			i += word_case(&line_lst, line + i, state);
		}
		else if (line[i] == '\"')
		{
			state = quotes(line_lst, line[i], state);
			i++;
		}
		else if (line[i] == '\'')
		{
			// printf("quotes");
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
		{
			i += space_case(&line_lst, state);
		}
		else
			i++;
		// printf("list = %s", line_lst->value);
	}
	return (line_lst);
}


int syntax_pipe(t_line_lst *line)
{
	if (line->prev == NULL || line->next == NULL || line->next->type == e_pipe)
	{
		printf("syntax_pipe faalt\n");
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
	// < file   of < $file
	if (line->type == e_redirect_i && line->next != NULL)
		if (line->next->type != e_file || line->next->type != e_var)
		{
			printf("syntax_redirects\tfaalt");
			return (1);
		}
	// file > of $file
	if (line->type == e_redirect_o && line->prev != NULL)
		
	if (line->type == e_append && line->prev != NULL)

	if (line->type == e_delimiter && line->next != NULL)

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
			printf("redirect\n");
		temp = temp->next;
	}
	return (0);
}