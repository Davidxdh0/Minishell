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

static bool		echo_option(char *str)
{
	int	i;

	if (str[0] != '-' && str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] == ' ') // might be a problem, test "-nnn XX"
			break ;
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return(true);
}

void	ft_echo(t_execute *cmd_struct, int fd)
{
	int		i;
	bool	n;
	i = 1;
	if (cmd_struct->cmd[i])
		n = echo_option(cmd_struct->cmd[i]);
	else
		n = false;
	if (n)
		i++;
	while (cmd_struct->cmd[i])
	{
		write(fd, cmd_struct->cmd[i], ft_strlen(cmd_struct->cmd[i]));
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}

void	ft_pwd(int fd)
{
	char	*buf;  // working directory name is capped (at 1024) by a certain rule, source needed

	buf = getcwd(NULL, 0);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
}

bool	ft_env(char **envp, int fd)
{
	int	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		write(fd, envp[i], strlen(envp[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (true);
}


int	ft_getenv_int(const char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (name[j] == envp[i][j])
		{
			j++;
			if (!name[j])
				return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_export(char *cmd, char **envp, int fd)
{
	char	*target;
	int		env;
	// char	*envstr;
	int		i;
	
	target = NULL;
	i = 0;
	// cmd_struct->cmd[1] = ft_strdup("TERM=YATTAAAA");
	while (cmd[i])
	{
		if (cmd[i] == '=' && i != 0)
		{
			i++;
			target = ft_substr(cmd, 0, i);
			printf("Export Target: %s\n", target);
			break ;
		}
		i++;
	}
	// return ;
	// target = (cut command on the '=' ), store the remainder in cmd
	// target = strdup("PWD=");
	if (target)
	{
		env = ft_getenv_int(target, envp);
		free(target);
		if (env >= 0)
			envp[env] = ft_strdup(cmd);
		// free(envp[env]); does this leak? why cant I free it?
		// envp[env] = strdup("PWD=/Users/znadja");
		else
		{
			i = 0;
			while (envp[i])
				i++;
			envp[i] = ft_strdup(cmd);
			envp[i + 1] = NULL;
		}
	}
	// envstr = ft_getenv(target, envp);
	// ft_strlcpy(envstr, strdup("PWD=/Users/znadja"), 10);
	// // If no need to free, this should work, but depending on space, just write into it?
	// ft_env(envp, 1);
}
void	ft_unset(char *cmd, char **envp, int fd)
{
	char	*target;
	int		env;
	int		i;
	
	i = 0;
	target = NULL;
	// cmd = ft_strdup("TERM=YATTAAAA");
	while (cmd[i])
	{
		if (cmd[i] == '=' && i != 0)
		{
			i++;
			target = ft_substr(cmd, 0, i);
			printf("Unset Target: %s\n", target);
			break ;
		}
		i++;
	}
	if (target)
	{
		env = ft_getenv_int(target, envp);
		free(target);
		while (envp[env + 1])
		{
			envp[env] = envp[env + 1];
			env++;
		}
		envp[env] = NULL;
	}
	// ft_env(envp, 1);
}
void	ft_cd(t_execute *cmd_struct, char **envp, char *path)
{
	int		i;
	char	*cwd;
	char	*cmd;

	cwd = getcwd(NULL, 0);
	i = chdir(path);
	if (i < 0)
	{
		printf("chdir return = %d\n", i);
		free(cwd);
		return ;
	}
	cmd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	ft_export(cmd, envp, 1);
	free(cmd);
	cwd = getcwd(NULL, 0);
	cmd = ft_strjoin("PWD=", cwd);
	free(cwd);
	ft_export(cmd, envp, 1);
	free(cmd);
	printf("Current PWD = %s\n", getcwd(NULL, 0));
}

void	ft_exit(t_execute *cmd_struct, char **envp)
{
	
}
