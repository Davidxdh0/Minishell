/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:43 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/13 19:47:22 by dyeboa        ########   odam.nl         */
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

int	str_isspaces(char **line)
{
	int i = 0;

	while(line[0][i])
	{
		if (line[0][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*
	Set the display name in the termian and reading the input from the termial
	what to do with empty? ""?
*/
void	line_reader(char **line, const char *display_name)
{
	// make_sure_line_is_empty(line);
	*line = readline(display_name);
	if (!line)
	{
		printf("exit\n");
		exit(1);
	}
	if (*line && **line && !str_isspaces(line))
		add_history (*line);
}
