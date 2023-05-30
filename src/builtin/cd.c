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
	if (!cmd)
		ft_exit_error("Malloc Failed", errno);
	ft_export_cmd(cmd, "OLDPWD=", envp, 1);
	free(cmd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_perror(cmd_struct->cmd[1], errno), false);
	cmd = ft_strjoin("PWD=", cwd);
	if (!cmd)
		ft_exit_error("Malloc Failed", errno);
	free(cwd);
	ft_export_cmd(cmd, "PWD=", envp, 1);
	free(cmd);
	// printf("Current PWD = %s\n", getcwd(NULL, 0));
	return (true);
}
