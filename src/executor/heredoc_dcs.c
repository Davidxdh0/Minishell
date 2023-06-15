/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:44:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/15 17:09:59 by dyeboa        ########   odam.nl         */
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

bool	heredoc_loop(char *eof, int fd, t_envp *new_envp)
{
	char	*line;
	bool	str;
	char	*new;

	new = NULL;
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
		if (find_variable(line))
			expand_heredoc_word(line, new_envp, fd);
		else
			ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		str = true;
	}
	free(line);
	return (str);
}

//this works, but signal don't
void	ft_heredoc(char *eof, char *name, t_envp *new_envp)
{
	int		fd;
	bool	str;

	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		exit(ft_perror(name, 1));
	str = true;
	while (str == true && g_exitcode != 1000)
		str = heredoc_loop(eof, fd, new_envp);
	close(fd);
}


	// {
	// 	line = readline("HereDoc> ");
	// 	if (!line)
	// 	{
	// 		rl_replace_line("", 0);
	// 		rl_on_new_line();
	// 		rl_redisplay();
	// 		str = false;
	// 	}
	// 	else if (!ft_strcmp(line, eof))
	// 		str = false;
	// 	else
	// 	{
	// 		ft_putstr_fd(line, fd);
	// 		write(fd, "\n", 1);
	// 	}
	// 	free(line);
	// }

void	ft_heredoc_init(t_execute *cmd_struct, t_envp *new_envp)
{
	int	i;
	int	count;

	count = 1;
	while (cmd_struct)
	{
		i = 0;
		cmd_struct->heredoc_name = NULL;
		while (cmd_struct->redirects && cmd_struct->redirects[i])
		{
			if (cmd_struct->redirects[i][0] == '<' &&
				cmd_struct->redirects[i][1] == '<')
			{
				if (cmd_struct->heredoc_name)
					unlink(cmd_struct->heredoc_name);
				i++;
				ft_heredoc_name(cmd_struct, count++);
				ft_heredoc(cmd_struct->redirects[i], cmd_struct->heredoc_name, new_envp);
				// if (g_exitcode == 1000)
				// 	false en g_exitcode 1;
			}
			i++;
		}
		cmd_struct = cmd_struct->next;
	}
}
