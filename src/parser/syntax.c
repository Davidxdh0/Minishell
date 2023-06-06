/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 16:27:35 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/06 14:53:02 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// printf("syntax error near unexpected token `|'\n");
int	syntax_pipe(t_line_lst *line)
{
	if (line->prev == NULL || line->next == NULL || line->next->type == e_pipe)
	{
		return (1);
	}
	return (0);
}

int	syntax_quotes(t_line_lst *line, node_type type)
{
	char	*str;

	while (line)
	{
		line = line->next;
		if (!line || line->type == (int)type)
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

int	syntax_count_quotes(t_line_lst *line)
{
	t_line_lst	*temp;
	int			dquote;
	int			quote;

	dquote = 2;
	quote = 2;
	temp = line;
	while (temp != NULL)
	{
		if (temp->state == 2 && ft_strcmp(temp->value, "\"") == 0)
			dquote++;
		if (temp->state == 1 && ft_strcmp(temp->value, "\'") == 0)
			quote++;
		temp = temp->next;
	}
	if (quote % 2 == 0 && dquote % 2 == 0)
		return (0);
	write(2, "minishell: Quotes are not balanced\n", 36);
	return (1);
}

int	syntax_redirects(t_line_lst *l)
{
	if (l->type == e_redirect_i)
		if (l->next == NULL || (l->next->type != e_file \
		&& l->next->type != e_var && l->prev->type != e_word \
		&& l->next->type != e_quote))
			return (1);
	if (l->type == e_redirect_o)
	{
		if (l->prev == NULL && l->next != NULL)
			return (0);
		else if (l->next == NULL)
			return (1);
		if (l->next->type != e_file && l->next->type != e_var && \
			l->next->type != e_word && l->next->type != e_quote && \
			l->next->type != e_cmd)
			return (1);
	}
	if (l->type == e_append)
		if (l->next == NULL || (l->next->type != e_file && l->next->type != \
		e_var && l->next->type != e_word && l->next->type != e_quote))
			return (1);
	if (l->type == e_delimiter)
		if (l->next == NULL || (l->next->type != e_file && l->next->type != \
		e_var && l->next->type != e_word && l->next->type != e_quote))
			return (1);
	return (0);
}

int	syntax_check(t_line_lst *line)
{
	t_line_lst	*temp;

	temp = line;
	while (temp != NULL)
	{
		if (temp->type == e_pipe)
			if (syntax_pipe(temp))
				return (perror_return("`|'"));
		if (temp->type == e_redirect_i || temp->type == e_append || \
			temp->type == e_redirect_o || temp->type == e_delimiter)
		{
			if (syntax_redirects(temp))
				return (perror_return("`newline'"));
		}
		temp = temp->next;
	}
	temp = line;
	return (0);
}
