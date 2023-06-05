/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 11:06:04 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/05 11:06:05 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static int	redirect_infile_extended(char *list, int *i, bool *file)
{
	int	fd;

	*i += 1;
	fd = open(list, O_RDONLY);
	if (fd == -1)
		exit(ft_perror(list, 1));
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(ft_perror(NULL, 1));
	close(fd);
	*file = true;
	return (fd);
}

bool	redirect_infile(char **list, char *name)
{
	int		i;
	bool	file;
	int		fd;

	file = false;
	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '<' && list[i][1] != '<')
			fd = redirect_infile_extended(list[i + 1], &i, &file);
		if (list[i][0] == '<' && list[i][1] == '<')
		{
			i++;
			fd = open(name, O_RDONLY);
			if (fd == -1)
				exit(ft_perror(list[i], 1));
			if (dup2(fd, STDIN_FILENO) == -1)
				exit(ft_perror(NULL, 1));
			close(fd);
			file = true;
		}
		i++;
	}
	return (file);
}

static int	redirect_outfile_extended(char *list, int *i, bool *file)
{
	int	fd;

	*i += 1;
	fd = open(list, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(ft_perror(list, 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(ft_perror(NULL, 1));
	close(fd);
	(*file) = true;
	return (fd);
}

bool	redirect_outfile(char **list)
{
	int		i;
	int		fd;
	bool	file;

	file = false;
	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '>' && !list[i][1])
			fd = redirect_outfile_extended(list[i + 1], &i, &file);
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			fd = open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd == -1)
				exit(ft_perror(list[i], 1));
			if (dup2(fd, STDOUT_FILENO) == -1)
				exit(ft_perror(NULL, 1));
			close(fd);
			file = true;
		}
		i++;
	}
	return (file);
}
