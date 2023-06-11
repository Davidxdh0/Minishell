/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:34:13 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/05 12:33:56 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

bool	find_env_in_list(t_envp *envp, char *str)
{
	while (envp)
	{
		if (!ft_strcmp(str, envp->identifier))
			return (true);
		envp = envp->next;
	}
	return (false);
}

static bool	cd_update_oldpwd(t_envp *envp)
{
	char	*cmd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror("getcwd: ", 1);
		return (false);
	}
	if (find_env_in_list(envp, "OLDPWD"))
	{
		cmd = ft_strjoin("OLDPWD=", cwd);
		ft_export_cmd(cmd, ft_strdup("OLDPWD"), envp, false);
		free(cmd);
	}
	free(cwd);
	return (true);
}

static bool	cd_update_pwd(t_envp *envp)
{
	char	*cmd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror("getcwd: ", 1);
		return (false);
	}
	if (find_env_in_list(envp, "PWD"))
	{
		cmd = ft_strjoin("PWD=", cwd);
		ft_export_cmd(cmd, ft_strdup("PWD"), envp, false);
		free(cmd);
	}
	free(cwd);
	return (true);
}

void	ft_cd(t_execute *cmd_struct, t_envp *envp)
{
	if (cd_update_oldpwd(envp))
		cd_update_pwd(envp);
	if (chdir(cmd_struct->cmd[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_perror(cmd_struct->cmd[1], 1);
	}
}
