/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:36:17 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:36:20 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static unsigned long long	string_to_ull(const char *str, bool neg)
{
	unsigned long long	atoi;

	atoi = 0;
	while (*str >= '0' && *str <= '9')
	{
		atoi *= 10;
		atoi += *str - 48;
		str++;
		if ((atoi > __LONG_LONG_MAX__) && (neg == false))
			return ((unsigned long long)__LONG_LONG_MAX__ + 2);
		if ((atoi > (unsigned long long)__LONG_LONG_MAX__ + 1) && (neg == true))
			return ((unsigned long long)__LONG_LONG_MAX__ + 3);
	}
	return (atoi);
}

bool	long_atoi(const char *str, long *number)
{
	unsigned long long	atoi;
	bool				neg;

	neg = false;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = true;
		str++;
	}
	atoi = string_to_ull(str, neg);
	if (atoi > (unsigned long long)__LONG_LONG_MAX__ + 1 || \
		(atoi > __LONG_LONG_MAX__ && neg == 0))
		return (false);
	if (atoi == (unsigned long long)__LONG_LONG_MAX__ + 1)
		*number = (__LONG_LONG_MAX__ * -1) - 1;
	else
	{
		*number = (long)atoi;
		if (neg == true)
			atoi *= -1;
	}
	return (true);
}

static char	*remove_plus_from_str(char *cmd)
{
	int		i;

	i = check_envp_value(cmd) - 1;
	cmd = ft_str_fuse(ft_substr(cmd, 0, i), \
		ft_substr(cmd, i + 1, ft_strlen(cmd) - (i + 1)));
	return (cmd);
}

static bool	export_targeted(char *cmd, char *target, t_envp *envp, bool append)
{
	while (envp)
	{
		if (!ft_strcmp(target, envp->identifier))
		{
			if (append)
				envp->line = ft_str_fuse(envp->line, ft_substr(cmd, \
				check_envp_value(cmd) + 1, ft_strlen(cmd) - \
				(check_envp_value(cmd) + 1)));
			else
			{
				free(envp->line);
				envp->line = ft_strdup(cmd);
			}
			free(envp->string);
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

t_envp	*ft_export_cmd(char *cmd, char *target, t_envp *envp, bool append)
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
	else if (export_targeted(cmd, target, envp, append))
		return (envp);
	envp = head;
	if (target && append)
		cmd = remove_plus_from_str(cmd);
	if (!envp)
		envp = envp_start_list(cmd);
	else
		envp_add_node(envp, cmd);
	if (target && append)
		free(cmd);
	return (envp);
}
