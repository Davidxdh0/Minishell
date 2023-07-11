/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:36:01 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/15 21:21:18 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	check_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strcmp(arg, "echo") == EXIT_SUCCESS)
		return (ECH);
	if (ft_strcmp(arg, "cd") == EXIT_SUCCESS)
		return (CD);
	if (ft_strcmp(arg, "pwd") == EXIT_SUCCESS)
		return (PWD);
	if (ft_strcmp(arg, "export") == EXIT_SUCCESS)
		return (EXPORT);
	if (ft_strcmp(arg, "unset") == EXIT_SUCCESS)
		return (UNSET);
	if (ft_strcmp(arg, "env") == EXIT_SUCCESS)
		return (ENV);
	if (ft_strcmp(arg, "exit") == EXIT_SUCCESS)
		return (EXIT);
	return (0);
}

t_envp	*exec_builtin(t_execute *cmd_struct, t_envp *envp, int fd)
{
	int	builtin;

	builtin = check_builtin(cmd_struct->cmd[0]);
	if (builtin != EXIT)
		g_exitcode = 0;
	if (builtin == ECH)
		ft_echo(cmd_struct, fd);
	else if (builtin == CD)
		ft_cd(cmd_struct, envp);
	else if (builtin == PWD)
		ft_pwd(fd);
	else if (builtin == EXPORT)
		envp = ft_export(cmd_struct, envp, fd);
	else if (builtin == UNSET)
		envp = ft_unset(cmd_struct, envp);
	else if (builtin == ENV)
		ft_env(envp, fd);
	else if (builtin == EXIT)
		ft_exit(cmd_struct);
	if (cmd_struct->count_cmd > 1)
		exit(g_exitcode);
	if (fd != 1 && close(fd) == -1)
		exit(ft_perror(NULL, 1, NULL));
	return (envp);
}

bool	builtin_infile(char **list)
{
	int	i;
	int	fd;

	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '<' && list[i][1] != '<')
		{
			fd = open(list[i + 1], O_RDONLY);
			if (fd == -1)
				return (ft_perror(list[i + 1], 1, NULL), false);
			if (close(fd) == -1)
				return (ft_perror(NULL, 1, NULL), false);
		}
		i += 2;
	}
	return (true);
}

bool	builtin_outfile(char **list, int *fd, int i, int temp_fd)
{
	while (list && list[i] && list[i + 1])
	{
		if (list[i][0] == '>' && !list[i][1])
		{
			if (temp_fd != -1 && close(temp_fd) == -1)
				return (ft_perror(NULL, 1, NULL), false);
			temp_fd = open(list[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (temp_fd == -1)
				return (ft_perror(list[i + 1], 1, NULL), false);
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			if (temp_fd != -1 && close(temp_fd) == -1)
				return (ft_perror(NULL, 1, NULL), false);
			temp_fd = open(list[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (temp_fd == -1)
				return (ft_perror(list[i + 1], 1, NULL), false);
		}
		i += 2;
	}
	if (temp_fd != -1)
		*(fd) = temp_fd;
	return (true);
}
