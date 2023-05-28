/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grammer_checker.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:02 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/28 19:24:35 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	is_valid_cmd(node_type last_type)
{
	if (last_type == e_start)
		return (1);
	if (last_type == e_pipe)
		return (1);
	return (0);
}

int	is_valid_pipe(node_type last_type)
{
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_file(node_type last_type)
{
	if (last_type == e_redirect_i)
		return (1);
	if (last_type == e_redirect_o)
		return (1);
	if (last_type == e_delimiter)
		return (1);
	if (last_type == e_append)
		return (1);
	return (0);
}

int	is_valid_word(node_type last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	if (last_type == e_var)
		return (1);
	return (0);
}

int	is_valid_var(node_type last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_quote(node_type last_type)
{
	if (last_type == e_whitespace)
		return (1);
	if (last_type == e_quote)
		return (1);
		if (last_type == e_dquote)
		return (1);
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_type(node_type type, t_line_lst *node)
{
	node_type	last_type;

	last_type = get_previous_type(node);
	if (type == e_cmd)
		return (is_valid_cmd(last_type));
	if (type == e_file)
		return (is_valid_file(last_type));
	if (type == e_pipe)
		return (is_valid_pipe(last_type));
	if (type == e_word)
		return (is_valid_word(last_type));
	if (type == e_whitespace)
		return (is_valid_word(last_type));
	if (type == e_var)
		return (is_valid_var(last_type));
	if (type == e_quote)
		return (is_valid_var(last_type));	
	if (type == e_dquote)
		return (is_valid_var(last_type));	
	return (0);
}

int	is_valid_grammer(t_line_lst *head)
{
	if (!head)
	{
		ft_putendl_fd("gammer is not valid", 1);
		return (0);
	}
	return (1);
}
