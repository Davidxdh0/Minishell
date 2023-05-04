/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:14 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:15 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_export_argless(t_execute *cmd_struct, char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

void	ft_export_cmd(char *cmd, char **envp, int fd)
{
	int		i;
	char	*target;

	target = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			target = ft_substr(cmd, 0, i + 1);
			if (!target)
				ft_exit_error("Malloc Failed", 2);
			printf("Export Target: %s\n", target);
			break ;
		}
		i++;
	}
	// target = ft_export_validation(cmd); //instead of all of the above
	if (target)
	{
		ft_getenv_int(&i, target, envp);
		free(target);
		if (i >= 0)
			envp[i] = ft_strdup(cmd);
		else
		{
			i = 0;
			while (envp[i])
				i++;
			envp[i] = ft_strdup(cmd);
			envp[i + 1] = NULL;
		}
	}
}

void	ft_export(t_execute *cmd_struct, char **envp, int fd)
{
	int		i;

printf("Entered Export\n");
	if (!cmd_struct->cmd[1])
		ft_export_argless(cmd_struct, envp, fd);
	else
	{
		i = 1;
		while (cmd_struct->cmd[i])
		{
			ft_export_cmd(cmd_struct->cmd[i], envp, fd);
			i++;
		}
	}
printf("Exiting Export\n");
}
