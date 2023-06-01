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

bool	export_characters(char c, bool start, char *str) //move to utils
{
	if (start == true)
	{
		if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
		{
			write(2, "minishell: export: `", 21);
			write(2, str, ft_strlen(str));
			write(2, "\': not a valid identifier\n", 26);
			return (false);
		}
	}
	else if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') \
			&& !(c >= '0' && c <= '9'))
	{
		write(2, "minishell: export: `", 21);
		write(2, str, ft_strlen(str));
		write(2, "\': not a valid identifier\n", 26);
		return (false);
	}
	return (true);
}

static bool	ft_export_validation(char *cmd, char **target)
{
	int		i;

	if (!export_characters(cmd[0], true, cmd))
		return (false);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			*target = ft_substr(cmd, 0, i);
			return (true);
		}
		if (!export_characters(cmd[i], false, cmd))
			return (false);
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
			free(target);
			free(envp->line);
			free(envp->string);
			envp->line = ft_strdup(cmd);
			if (!envp->value)
				envp->value = check_envp_value(envp->line);
			envp->string = ft_substr(envp->line, envp->value + 1 \
			, ft_strlen(envp->line) - (envp->value + 1));
			return (true);
		}
		envp = envp->next;
	}
	free(target);
	return (false);
}

t_envp	*ft_export_cmd(char *cmd, char *target, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	if (!target)
	{
		while (envp)
		{
			if (!ft_strcmp(cmd, envp->identifier))
				return (head);
			envp = envp->next;
		}
	}
	else if (export_targeted(cmd, target, envp))
		return (envp);
	envp = head;
	if (!envp)
		envp = envp_start_list(cmd);
	else
		envp_add_node(envp, cmd);
	return (envp);
}

void	ft_export_argless(t_envp *envp, int fd)
{
	while (envp)
	{
		write(fd, "declare -x ", 11);
		if (envp->value)
		{
			write(fd, envp->identifier, ft_strlen(envp->identifier));
			write(fd, "=\"", 2);
			write(fd, envp->string, ft_strlen(envp->string));
			write(fd, "\"\n", 2);
		}
		else
		{
			write(fd, envp->line, ft_strlen(envp->line));
			write(fd, "\n", 1);
		}
		envp = envp->next;
	}
}

t_envp	*ft_export(t_execute *cmd_struct, t_envp *envp, int fd)
{
	int		i;
	char	*target;

	if (!cmd_struct->cmd[1])
		ft_export_argless(envp, fd);
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
