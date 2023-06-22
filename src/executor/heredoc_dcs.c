/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:44:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/20 19:50:31 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	realign_heredoc_prompt(void)
{
	printf("\033[1A");
	printf("\033[K");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (false);
}

static void	ft_heredoc_name(t_execute *cmd_struct, int cmd_nbr)
{
	char	*number;

	number = ft_itoa(cmd_nbr);
	cmd_struct->heredoc_name = ft_strjoin(".heredoc", number);
	free(number);
}

static bool	heredoc_loop(char *eof, int fd, t_envp *new_envp)
{
	char	*line;
	bool	str;

	if (g_exitcode == 1000)
		return (false);
	line = readline("HereDoc> ");
	if (!line)
		str = realign_heredoc_prompt();
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

static bool	ft_heredoc(char *eof, char *name, t_envp *new_envp)
{
	int		fd;
	bool	str;

	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (ft_perror(name, 1, NULL), false);
	str = true;
	while (str == true && g_exitcode != 1000)
		str = heredoc_loop(eof, fd, new_envp);
	close(fd);
	if (g_exitcode == 1000)
		return (false);
	return (true);
}

bool	ft_heredoc_init(t_execute *cmd_s, t_envp *envp)
{
	int	i;
	int	count;

	count = 1;
	while (cmd_s)
	{
		i = 0;
		while (cmd_s->redirects && cmd_s->redirects[i])
		{
			if (cmd_s->redirects[i][0] == '<' &&
				cmd_s->redirects[i][1] == '<')
			{
				if (cmd_s->heredoc_name)
					unlink(cmd_s->heredoc_name);
				i++;
				ft_heredoc_name(cmd_s, count++);
				if (!ft_heredoc(cmd_s->redirects[i], cmd_s->heredoc_name, envp))
					return (false);
			}
			i++;
		}
		cmd_s = cmd_s->next;
	}
	return (true);
}
