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

static int	redirect_infile_extended(char *name, bool *file)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit(ft_perror(name, 1, NULL));
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(ft_perror(NULL, 1, NULL));
	close(fd);
	g_exitcode = 0;
	*file = true;
	return (fd);
}

bool	redirect_infile(char **list, char *heredoc_name)
{
	int		i;
	bool	file;
	int		fd;

	file = false;
	i = 0;
	while (list && list[i] && list[i + 1])
	{
		if (list[i][0] == '<' && list[i][1] != '<')
			fd = redirect_infile_extended(list[i + 1], &file);
		if (list[i][0] == '<' && list[i][1] == '<')
		{
			fd = open(heredoc_name, O_RDONLY);
			if (fd == -1)
				exit(ft_perror(list[i + 1], 1, NULL));
			if (dup2(fd, STDIN_FILENO) == -1)
				exit(ft_perror(NULL, 1, NULL));
			close(fd);
			g_exitcode = 0;
			file = true;
		}
		i += 2;
	}
	return (file);
}

static int	redirect_outfile_extended(char *name, bool *file)
{
	int	fd;

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(ft_perror(name, 1, NULL));
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(ft_perror(NULL, 1, NULL));
	close(fd);
	g_exitcode = 0;
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
	while (list && list[i] && list[i + 1])
	{
		if (list[i][0] == '>' && !list[i][1])
			fd = redirect_outfile_extended(list[i + 1], &file);
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			fd = open(list[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (fd == -1)
				exit(ft_perror(list[i + 1], 1, NULL));
			if (dup2(fd, STDOUT_FILENO) == -1)
				exit(ft_perror(NULL, 1, NULL));
			close(fd);
			g_exitcode = 0;
			file = true;
		}
		i += 2;
	}
	return (file);
}
