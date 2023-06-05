/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:36 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:40 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	unset_characters(char c, bool start, char *str)
{
	if (start == true)
	{
		if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			return (false);
		}
	}
	else if (!(c == '_') && !(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') \
			&& !(c >= '0' && c <= '9'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (false);
	}
	return (true);
}

static bool	unset_validation(char *cmd)
{
	int	i;

	if (!unset_characters(cmd[0], true, cmd))
		return (g_exitcode = 1, false);
	i = 1;
	while (cmd[i])
	{
		if (!unset_characters(cmd[i], false, cmd))
			return (g_exitcode = 1, false);
		i++;
	}
	return (true);
}

t_envp	*ft_unset(t_execute *cmd_struct, t_envp *envp)
{
	t_envp	*head;
	int		i;

	i = 1;
	head = envp;
	while (cmd_struct->cmd[i])
	{
		if (unset_validation(cmd_struct->cmd[i]))
		{
			envp = head;
			while (envp)
			{
				if (!ft_strcmp(cmd_struct->cmd[i], envp->identifier))
				{
					head = remove_envp_node(envp);
					break ;
				}
				envp = envp->next;
			}
		}
		i++;
	}
	return (envp);
}
