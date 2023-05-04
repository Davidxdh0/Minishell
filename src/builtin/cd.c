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

void	ft_cd(t_execute *cmd_struct, char **envp, char *path)
{
	int		i;
	char	*cwd;
	char	*cmd;

	cwd = getcwd(NULL, 0);
	i = chdir(path);
	if (i < 0)
	{
		printf("Chdir Return = %d\n", i); // errors and shit
		free(cwd);
		return ;
	}
	cmd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	ft_export_cmd(cmd, envp, 1);
	free(cmd);
	cwd = getcwd(NULL, 0);
	cmd = ft_strjoin("PWD=", cwd);
	free(cwd);
	ft_export_cmd(cmd, envp, 1);
	free(cmd);
	printf("Current PWD = %s\n", getcwd(NULL, 0));
}
