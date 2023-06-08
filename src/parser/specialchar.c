/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specialchar.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/08 11:45:12 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	pipe_c(t_line_lst **line_lst, int state)
{
	add_at_end_of_list(line_lst, e_pipe, "|", state);
	return (1);
}

int	space_c(t_line_lst **line_lst, int state)
{
	add_at_end_of_list(line_lst, e_wspace, " ", state);
	return (1);
}

int	delim_c(t_line_lst **line_lst, char *line, int state)
{
	if (line[1] == '<')
	{
		add_at_end_of_list(line_lst, e_delimiter, "<<", state);
		return (2);
	}
	add_at_end_of_list(line_lst, e_redirect_i, "<", state);
	return (1);
}

int	redirect_c(t_line_lst **line_lst, char *line, int state)
{
	if (line[1] == '>')
	{
		add_at_end_of_list(line_lst, e_append, ">>", state);
		return (2);
	}
	add_at_end_of_list(line_lst, e_redirect_o, ">", state);
	return (1);
}
