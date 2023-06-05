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

// cant start with a number
// cant have special characters
// += (dont need to handle)
// sorting (not handling)

static bool	export_characters(char c, bool start, char *str)
{
	if (start == true)
	{
		if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (false);
		}
	}
	else if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') \
			&& !(c >= '0' && c <= '9'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (false);
	}
	return (true);
}

static bool	ft_export_validation(char *cmd, char **target)
{
	int		i;

	if (!export_characters(cmd[0], true, cmd))
		return (g_exitcode = 1, false);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			*target = ft_substr(cmd, 0, i);
			return (true);
		}
		if (!export_characters(cmd[i], false, cmd))
			return (g_exitcode = 1, false);
		i++;
	}
	return (true);
}

bool	export_targeted(char *cmd, char *target, t_envp *envp)
{
	while (envp)
	{
		if (!ft_strcmp(target, envp->identifier))
		{
			free(envp->line);
			free(envp->string);
			envp->line = ft_strdup(cmd);
			if (!envp->value)
				envp->value = check_envp_value(envp->line);
			envp->string = ft_substr(envp->line, envp->value + 1 \
			, ft_strlen(envp->line) - (envp->value + 1));
			free(target);
			return (true);
		}
		envp = envp->next;
	}
	free(target);
	return (false);
}

static void	export_argless(t_envp *envp, int fd)
{
	while (envp)
	{
		ft_putstr_fd("declare -x ", fd);
		if (envp->value)
		{
			ft_putstr_fd(envp->identifier, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(envp->string, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
		{
			ft_putstr_fd(envp->line, fd);
			ft_putstr_fd("\n", fd);
		}
		envp = envp->next;
	}
}

t_envp	*ft_export(t_execute *cmd_struct, t_envp *envp, int fd)
{
	int		i;
	char	*target;

	if (!cmd_struct->cmd[1])
		export_argless(envp, fd);
	else
	{
		i = 1;
		while (cmd_struct->cmd[i])
		{
			target = NULL;
			if (ft_export_validation(cmd_struct->cmd[i], &target))
				envp = ft_export_cmd(cmd_struct->cmd[i], target, envp);
			i++;
		}
	}
	return (envp);
}
