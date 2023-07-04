/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_validation.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 16:11:33 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/26 16:11:34 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	validate_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_perror(file, 1, NULL);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	validate_outfile_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_perror(file, 1, NULL);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	validate_outfile_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_perror(file, 1, NULL);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	validate_file(char *str, char *file)
{
	if (str[0] == '>' && str[1] != '>')
		return (validate_outfile_trunc(file));
	if (str[0] == '>' && str[1] == '>')
		return (validate_outfile_append(file));
	if (str[0] == '<' && str[1] != '<')
		return (validate_infile(file));
	return (true);
}

bool	validate_redirects(t_execute *cmd_struct)
{
	int	i;

	i = 0;
	if (cmd_struct->redirects)
	{
		while (cmd_struct->redirects[i])
		{
			if (!validate_file(cmd_struct->redirects[i] \
				, cmd_struct->redirects[i + 1]))
			{
				g_exitcode = 1;
				return (false);
			}
			i++;
		}
	}
	return (true);
}
