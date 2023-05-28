/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/21 08:28:28 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_argv_in_line(int argc, char *argv[], char **line)
{
	int	index;

	index = 2;
	*line = &argv[1][index];
	while (index < argc)
	{
		*line = ft_strjoin(*line, argv[index]);
		// printf("line = %s\n", *line);
		index++;
		if (index < argc)
			*line = ft_strjoin(*line, " ");
	}
}

int	argv_has_flag(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	if (ft_strlen(argv[1]) < 2)
		return (0);
	if (ft_strncmp(argv[1], "-p", ft_strlen(argv[1])) != 0)
		return (0);
	return (1);
}

int	input_is_argv(int argc, char *argv[], char **line)
{
	if (!argv_has_flag(argc, argv))
		return (0);
	put_argv_in_line(argc, argv, line);
	return (1);
}
