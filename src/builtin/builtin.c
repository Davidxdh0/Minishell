/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:36:01 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:36:02 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	check_builtin(char *arg)
{
	if (ft_strcmp(arg, "echo") == EXIT_SUCCESS)
		return (ECHO);
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

void	exec_builtin(t_execute *cmd_struct, char **envp, int fd)
{
	int	builtin;

	builtin = check_builtin(cmd_struct->cmd[0]);
	if (builtin == ECHO)
		ft_echo(cmd_struct, fd);
	else if (builtin == CD)
		ft_cd(cmd_struct, envp, cmd_struct->cmd[1]);
	else if (builtin == PWD)
		ft_pwd(fd);
	else if (builtin == EXPORT)
		ft_export(cmd_struct, envp, fd);
	else if (builtin == UNSET)
		ft_unset(cmd_struct, envp, fd);
	else if (builtin == ENV)
		ft_env(envp, fd);
	else if (builtin == EXIT)
		ft_exit(cmd_struct, envp);
	// reset_builtin_redirects(cmd_struct);
	printf("EXEC Builtin, END\n");
	if (cmd_struct->count_cmd > 1)
		exit(0);
}
