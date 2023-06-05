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

<<<<<<< HEAD
	updated_pwd = ft_strjoin("OLDPWD=", oldpath);
	while(*data->envp != NULL)
	{
		if (!strncmp(*data->envp, "OLDPWD=", 7))
			ft_strlcpy(*data->envp, updated_pwd, ft_strlen(updated_pwd));
		data->envp++;
	}
	free(updated_pwd);
}

void	cd_home(char **envp)
{
	while(*envp != NULL)
	{
		if (!strncmp(*envp, "HOME=", 5))
			change_dir(*envp+5, "");
		envp++;
	}
}

int		change_dir(char *oldpath, char *path)
{
	char *new_dir_slash;
	char *new_dir;

	new_dir_slash = ft_strjoin(oldpath, "/");
	new_dir = ft_strjoin(new_dir_slash, path);
	if (chdir(new_dir) != 0)
	{
		//write(1, "chdir\n", 7);
		return(1);
	}
	free(new_dir_slash);
	free(new_dir);
	return(0);
}

void	execute_cd(char **cmd, t_data *data)
{
	char 	*oldpath;
	int		status;
    char    cwd[4096 + 1];
	
	status = 0;
	oldpath = getcwd(cwd, 4097);
	
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		cd_home(data->envp);
	else if (cmd[1][0] == '.' && cmd[1][1] == '\0')
		;//update old pwd
	else if (cmd[1][0] == '.' && cmd[1][1] == '.')
	{
		//werkt niet, laatste woord moet eraf.
		change_dir(oldpath, cmd[1]);
	}
	else
		status = change_dir(oldpath, cmd[1]);
	if (status == 0)
		printf("test"); //update_old_pwd( oldpath, data);
	//free(oldpath);
=======
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
>>>>>>> 9b998d2321451c53440fe156fb178b317305482a
}
