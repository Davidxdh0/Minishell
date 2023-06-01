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
		{
			return (true);
		}
		envp = envp->next;
	}
	return (false);
}

bool	ft_cd(t_execute *cmd_struct, t_envp *envp)
{
	int		i;
	char	*cwd;
	char	*cmd;

	cwd = getcwd(NULL, 0);
	i = chdir(cmd_struct->cmd[1]);
	if (!cwd || i < 0)
		return (ft_perror(cmd_struct->cmd[1], errno), free(cwd), false);
	cmd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (find_env_in_list(envp, "OLDPWD"))
		ft_export_cmd(cmd, "OLDPWD", envp);
	free(cmd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_perror(cmd_struct->cmd[1], errno), false);
	cmd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (find_env_in_list(envp, "PWD"))
		ft_export_cmd(cmd, "PWD", envp);
	free(cmd);
	return (true);
}
