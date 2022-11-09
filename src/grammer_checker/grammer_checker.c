/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grammer_checker.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 11:23:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/09 16:02:11 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "grammer_checker.h"

int	is_valid_cmd(t_note last_type)
{
	if (last_type == e_start)
		return (1);
	if (last_type == e_pipe)
		return (1);
	return (0);
}

int	is_valid_pipe(t_note last_type)
{
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_file(t_note last_type)
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

int	is_valid_word(t_note last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	if (last_type == e_var)
		return (1);
	return (0);
}

int	is_valid_var(t_note last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_type(t_note type, t_line_lst *node)
{
	t_note	last_type;

	last_type = get_last_type(node);
	if (type == e_cmd)
		return (is_valid_cmd(last_type));
	if (type == e_file)
		return (is_valid_file(last_type));
	if (type == e_pipe)
		return (is_valid_pipe(last_type));
	if (type == e_word)
		return (is_valid_word(last_type));
	if (type == e_var)
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
