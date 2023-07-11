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

static bool	ft_heredoc_name(t_execute *cmd_struct, int *fd, int cmd_nbr)
{
	char	*number;

	if (cmd_struct->heredoc_name)
		unlink(cmd_struct->heredoc_name);
	number = ft_itoa(cmd_nbr);
	cmd_struct->heredoc_name = ft_strjoin(".heredoc", number);
	free(number);
	*fd = open(cmd_struct->heredoc_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	while (errno == EEXIST)
	{
		errno = 0;
		free(cmd_struct->heredoc_name);
		cmd_nbr += 10;
		number = ft_itoa(cmd_nbr);
		cmd_struct->heredoc_name = ft_strjoin(".heredoc", number);
		free(number);
		*fd = open(cmd_struct->heredoc_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	}
	if (*fd == -1)
		return (ft_perror(cmd_struct->heredoc_name, 1, NULL), false);
	return (true);
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

static bool	ft_heredoc(char *eof, int fd, t_envp *new_envp)
{
	bool	str;

	str = true;
	sig_controller(1);
	while (str == true && g_exitcode != 1000)
		str = heredoc_loop(eof, fd, new_envp);
	close(fd);
	sig_controller(2);
	if (g_exitcode == 1000)
		return (false);
	return (true);
}

bool	ft_heredoc_init(t_execute *cmd_s, t_envp *envp)
{
	int	i;
	int	count;
	int	fd;

	fd = 0;
	count = 1;
	while (cmd_s)
	{
		i = 0;
		while (cmd_s->redirects && \
			cmd_s->redirects[i] && cmd_s->redirects[i + 1])
		{
			if (cmd_s->redirects[i][0] == '<' &&
				cmd_s->redirects[i][1] == '<')
			{
				if (!ft_heredoc_name(cmd_s, &fd, count++))
					return (false);
				if (!ft_heredoc(cmd_s->redirects[i + 1], fd, envp))
					return (false);
			}
			i += 2;
		}
		cmd_s = cmd_s->next;
	}
	return (true);
}
