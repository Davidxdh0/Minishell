/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:34:13 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:34:15 by abarteld      ########   odam.nl         */
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
	cmd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (find_env_in_list(envp, "OLDPWD"))
		ft_export_cmd(cmd, ft_strdup("OLDPWD"), envp);
	free(cmd);
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
	cmd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (find_env_in_list(envp, "PWD"))
		ft_export_cmd(cmd, ft_strdup("PWD"), envp);
	free(cmd);
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
