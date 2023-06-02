/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:44:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/04/09 18:44:50 by abarteld      ########   odam.nl         */
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
	printf("ItoA result = %s\n", number);
	if (!number)
		ft_exit_error("Malloc Failed", 2);
	cmd_struct->heredoc_name = ft_strjoin(".heredoc", number);
	if (!cmd_struct->heredoc_name)
		ft_exit_error("Malloc Failed", 2);
	free(number);
}

bool	ft_heredoc(char *eof, char *name)
{
printf("\nHere In This DOC\n");
	char	*line;
	int		fd;
	bool	str;

	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		ft_exit_error("Heredoc Tempfile Create Error", 16);
	line = NULL;
	str = true;
	while (str == true)
	{
		line = readline("HereDoc> ");
		if (!line)
			ft_exit_error("Readline Error", 17);
		if (!ft_strcmp(line, eof))
			str = false;
		else
		{
			ft_putstr_fd(line, fd);
			write(fd, "\n", 1);
		}
		free(line);
	}
	close(fd);
printf("\nFuck this DOC, I'm Out\n");
	return (true);
}

void	ft_heredoc_init(t_execute *cmd_struct)
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
			if (cmd_struct->redirects[i][0] == '<' && cmd_struct->redirects[i][1] == '<')
			{
				if (cmd_struct->heredoc_name)
					unlink(cmd_struct->heredoc_name);
				i++;
				ft_heredoc_name(cmd_struct, count++);
				ft_heredoc(cmd_struct->redirects[i], cmd_struct->heredoc_name);
			}
			i++;
		}
		cmd_struct = cmd_struct->next;
	}
}