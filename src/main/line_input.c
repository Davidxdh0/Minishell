/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 16:57:52 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 16:59:43 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_sure_line_is_empty(char **line)
{
	if (*line)
	{
		free (*line);
		*line = (char *) NULL;
	}
}

void	add_line_in_history(char **line)
{
	if (*line && **line)
		add_history (*line);
}

/*
	Set the display name in the termian and reading the input from the termial
*/
void	line_reader(char **line, const char *display_name)
{
	make_sure_line_is_empty(line);
	*line = readline(display_name);
	add_line_in_history(line);
}
