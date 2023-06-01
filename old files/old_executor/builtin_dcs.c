/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 16:19:18 by abarteld      #+#    #+#                 */
/*   Updated: 2023/04/02 16:19:22 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

// use fds instead of dup2

// int	check_builtin(char *arg)
// {
// 	if (ft_strcmp(arg, "echo") == EXIT_SUCCESS)
// 		return (ECHO);
// 	if (ft_strcmp(arg, "cd") == EXIT_SUCCESS)
// 		return (CD);
// 	if (ft_strcmp(arg, "pwd") == EXIT_SUCCESS)
// 		return (PWD);
// 	if (ft_strcmp(arg, "export") == EXIT_SUCCESS)
// 		return (EXPORT);
// 	if (ft_strcmp(arg, "unset") == EXIT_SUCCESS)
// 		return (UNSET);
// 	if (ft_strcmp(arg, "env") == EXIT_SUCCESS)
// 		return (ENV);
// 	if (ft_strcmp(arg, "exit") == EXIT_SUCCESS)
// 		return (EXIT);
// 	return (0);
// }

// void	reset_builtin_redirects(t_execute *cmd_struct)
// {
// 	if (dup2(cmd_struct->std_fds[STDIN_FILENO], STDIN_FILENO) == -1)
// 		ft_exit_error("Couldn't Reset Standard In\n", errno); //errors and stuff
// 	if (dup2(cmd_struct->std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
// 		ft_exit_error("Couldn't Reset Standard Out\n", errno); //errors and stuff
// }

// void	exec_builtin(t_execute *cmd_struct, char **envp)
// {
// 	int	builtin;
// 	int fd;

// 	fd = 1;
// 	builtin = check_builtin(cmd_struct->cmd[0]);
// 	if (builtin == ECHO)
// 		ft_echo(cmd_struct, fd);
// 	else if (builtin == CD)
// 		ft_cd(cmd_struct, envp, cmd_struct->cmd[1]);
// 	else if (builtin == PWD)
// 		ft_pwd(fd);
// 	else if (builtin == EXPORT)
// 		ft_export(cmd_struct, envp, fd);
// 	else if (builtin == UNSET)
// 		ft_unset(cmd_struct, envp, fd);
// 	else if (builtin == ENV)
// 		ft_env(envp, fd);
// 	else if (builtin == EXIT)
// 		ft_exit(cmd_struct, envp);
// 	// reset_builtin_redirects(cmd_struct);
// 	printf("EXEC Builtin, END\n");
// 	if (cmd_struct->count_cmd > 1)
// 		exit(0);
// }

// static bool	echo_option(char *str)
// {
// 	int	i;

// 	if (str[0] != '-' && str[1] != 'n')
// 		return (false);
// 	i = 2;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ') // might be a problem, test "-nnn XX"
// 			break ;
// 		if (str[i] != 'n')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// void	ft_echo(t_execute *cmd_struct, int fd)
// {
// 	int		i;
// 	bool	n;

// 	i = 1;
// 	if (cmd_struct->cmd[i])
// 		n = echo_option(cmd_struct->cmd[i]);
// 	else
// 		n = false;
// 	if (n)
// 		i++;
// 	while (cmd_struct->cmd[i])
// 	{
// 		write(fd, cmd_struct->cmd[i], ft_strlen(cmd_struct->cmd[i]));
// 		i++;
// 	}
// 	if (!n)
// 		write(fd, "\n", 1);
// }

// void	ft_pwd(int fd)
// {
// 	char	*buf; // wd name capped (at 1024) by a certain rule, source needed

// 	buf = getcwd(NULL, 0);
// 	write(fd, buf, ft_strlen(buf));
// 	write(fd, "\n", 1);
// }

// bool	ft_env(char **envp, int fd)
// {
// 	int	i;

// 	if (!envp)
// 		return (false);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		write(fd, envp[i], ft_strlen(envp[i]));
// 		write(fd, "\n", 1);
// 		i++;
// 	}
// 	return (true);
// }

// bool	ft_getenv_int(int *env, const char *name, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!name | !envp)
// 		return (false);
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (name[j] == envp[i][j])
// 		{
// 			j++;
// 			if (!name[j])
// 			{
// 				*env = i;
// 				return (true);
// 			}
// 		}
// 		i++;
// 	}
// 	*env = -1;
// 	return (false);
// }

// void	ft_export_argless(t_execute *cmd_struct, char **envp, int fd)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("declare -x %s\n", envp[i]);
// 		i++;
// 	}
// }

// void	ft_export_cmd(char *cmd, char **envp, int fd)
// {
// 	int		i;
// 	char	*target;

// 	target = NULL;
// 	i = 0;
// 	// target = ft_export_validation(cmd);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '=')
// 		{
// 			target = ft_substr(cmd, 0, i + 1);
// 			if (!target)
// 				ft_exit_error("Malloc Failed", 2);
// 			printf("Export Target: %s\n", target);
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (target)
// 	{
// 		ft_getenv_int(&i, target, envp);
// 		free(target);
// 		if (i >= 0)
// 			envp[i] = ft_strdup(cmd);
// 		else
// 		{
// 			i = 0;
// 			while (envp[i])
// 				i++;
// 			envp[i] = ft_strdup(cmd);
// 			envp[i + 1] = NULL;
// 		}
// 	}
// }

// void	ft_export(t_execute *cmd_struct, char **envp, int fd)
// {
// 	int		i;

// printf("Entered Export\n");
// 	if (!cmd_struct->cmd[1])
// 		ft_export_argless(cmd_struct, envp, fd);
// 	else
// 	{
// 		i = 1;
// 		while (cmd_struct->cmd[i])
// 		{
// 			ft_export_cmd(cmd_struct->cmd[i], envp, fd);
// 			i++;
// 		}
// 	}
// printf("Exiting Export\n");
// 	// ft_env(envp, 1);
// }

// void	ft_unset(t_execute *cmd_struct, char **envp, int fd)
// {
// 	int		env;
// 	int		i;
// 	char	*name;

// ft_env(envp, 1);
// /*
// 	argument:
// 	string
// 	check for forbidden characters
// 	strjoin string + '='
// 	if string = variable
// 		delete variable

// 	next argument
// */

// 	if (!cmd_struct->cmd[1])
// 		ft_exit_error("Unset Error Message", 20);
// 	i = 1;
// 	while (cmd_struct->cmd[i])
// 	{
// 		// Validate Args
// 		name = ft_strjoin(cmd_struct->cmd[i], "=");
// 		if (!name)
// 			ft_exit_error("Malloc Failed", 2);
// 		if (ft_getenv_int(&env, name, envp))
// 		{
// 			while (envp[env])
// 			{
// 				envp[env] = envp[env + 1];
// 				env++;
// 			}
// 		}
// 		free(name);
// 		i++;
// 	}
// ft_env(envp, 1);
// }

// void	ft_cd(t_execute *cmd_struct, char **envp, char *path)
// {
// 	int		i;
// 	char	*cwd;
// 	char	*cmd;

// 	cwd = getcwd(NULL, 0);
// 	i = chdir(path);
// 	if (i < 0)
// 	{
// 		printf("Chdir Return = %d\n", i);
// 		free(cwd);
// 		return ;
// 	}
// 	cmd = ft_strjoin("OLDPWD=", cwd);
// 	free(cwd);
// 	ft_export_cmd(cmd, envp, 1);
// 	free(cmd);
// 	cwd = getcwd(NULL, 0);
// 	cmd = ft_strjoin("PWD=", cwd);
// 	free(cwd);
// 	ft_export_cmd(cmd, envp, 1);
// 	free(cmd);
// 	printf("Current PWD = %s\n", getcwd(NULL, 0));
// }

// void	ft_exit(t_execute *cmd_struct, char **envp) // add an fd?
// {
// 	// write(1, "Exit\n", 5);
// 	// if (cmd_struct->next || cmd_struct->prev)
// 	// 	return (EXIT_FAILURE); // it doesnt work when piped, still needs to throw errors first
// 	// if (!cmd_struct->cmd[1])
// 	// {
// 	// 	// free(shit that needs freeing);
// 	// 	// return (exit status)
// 	// }
// 	// else if (cmd_struct->cmd[2])
// 	// {
// 	// 	// error: too many argument
// 	// }
// 	// // check if arg 1 is 
// }
