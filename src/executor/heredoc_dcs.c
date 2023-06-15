/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:44:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/15 15:07:38 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_heredoc_cleanup(t_execute *cmd_struct)
{
	while (cmd_struct)
	{
		if (cmd_struct->heredoc_name)
		{
			unlink(cmd_struct->heredoc_name);
			free(cmd_struct->heredoc_name);
			cmd_struct->heredoc_name = NULL;
		}
		cmd_struct = cmd_struct->next;
	}
}

void	ft_heredoc_name(t_execute *cmd_struct, int cmd_nbr)
{
	char	*number;

	number = ft_itoa(cmd_nbr);
	cmd_struct->heredoc_name = ft_strjoin(".heredoc", number);
	free(number);
}

bool	heredoc_loop(char *eof, int fd)
{
	char	*line;
	bool	str;
	
	if (g_exitcode == 1000)
	{
		g_exitcode = 1;
		return (false);
	}
	line = readline("HereDoc> ");
	if (!line)
	{
		printf("\033[1A");
    	printf("\033[K");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		str = false;
	}
	else if (!ft_strcmp(line, eof))
		str = false;
	else
	{
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		str = true;
	}
	free(line);
	return (str);
}

bool	ft_heredoc(char *eof, char *name)
{
	int		fd;
	bool	str;

	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (ft_perror(name, 1, NULL), false);
	str = true;
	while (str == true && g_exitcode != 1000)
		str = heredoc_loop(eof, fd);
	close(fd);
	if (g_exitcode == 1000)
		return (false);
	return (true);
}

bool	ft_heredoc_init(t_execute *cmd_strc)
{
	int	i;
	int	count;

	count = 1;
	while (cmd_strc)
	{
		i = 0;
		cmd_strc->heredoc_name = NULL;
		while (cmd_strc->redirects && cmd_strc->redirects[i])
		{
			if (cmd_strc->redirects[i][0] == '<' &&
				cmd_strc->redirects[i][1] == '<')
			{
				if (cmd_strc->heredoc_name)
					unlink(cmd_strc->heredoc_name);
				i++;
				ft_heredoc_name(cmd_strc, count++);
				if (!ft_heredoc(cmd_strc->redirects[i], cmd_strc->heredoc_name))
					return (false);
			}
			i++;
		}
		cmd_strc = cmd_strc->next;
	}
	return (true);
}
