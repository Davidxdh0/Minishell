/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:43 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/20 20:23:17 by dyeboa        ########   odam.nl         */
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
	int	i;

	i = 0;
	while (line[0][i])
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
	*line = readline(display_name);
	if (*line == NULL)
	{
		g_exitcode = 0;
		printf("\033[1A");
		printf("\033[K");
		printf("minishell$ exit\n");
		exit(1);
	}
	if (*line && **line && !str_isspaces(line))
		add_history(*line);
}

int	check_combine(t_line_lst *cur)
{
	if ((!ft_strcmp(cur->value, "\'") && cur->state == 2) || \
			(!ft_strcmp(cur->value, "\"") && cur->state == 1))
		return (0);
	cur->state = 0;
	return (1);
}

void	putstrherdoc(int fd)
{
	char *str;
	
	str = ft_itoa(g_exitcode);
	ft_putstr_fd(str, fd);
	free(str);
}
