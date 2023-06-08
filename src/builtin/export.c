/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:14 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/05 12:34:13 by dyeboa        ########   odam.nl         */
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

static bool	ft_export_validation(char *cmd, t_export *target)
{
	int		i;

	if (!export_characters(cmd[0], true, cmd))
		return (g_exitcode = 1, false);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i] == '=' || (cmd[i] == '+' && cmd[i + 1] == '='))
		{
			if (cmd[i] == '+')
				target->append = true;
			if (cmd[i] == '+')
				i++;
			else
				target->append = false;
			target->str = ft_substr(cmd, 0, i - target->append);
			return (true);
		}
		if (!export_characters(cmd[i], false, cmd))
			return (g_exitcode = 1, false);
		i++;
	}
	target->str = NULL;
	target->append = false;
	return (true);
}

//	line = id + string
//	cmd = id + new_string (new line)
//	append_line = id + string + newstring

/*
As It Turns Out, Calling Export Without Any Arguments Doesn't Need To Display
Anything. The Current Bash Behaviour Is Technically Undefined.
*/
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
	int			i;
	t_export	target;

	if (!cmd_struct->cmd[1])
		export_argless(envp, fd);
	else
	{
		i = 1;
		while (cmd_struct->cmd[i])
		{
			if (ft_export_validation(cmd_struct->cmd[i], &target))
				envp = ft_export_cmd(cmd_struct->cmd[i], \
										target.str, envp, target.append);
			i++;
		}
	}
	return (envp);
}
