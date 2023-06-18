/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/18 18:08:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/18 18:08:52 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static char	*remove_plus_from_str(char *cmd)
{
	int		i;

	i = check_envp_value(cmd) - 1;
	cmd = ft_str_fuse(ft_substr(cmd, 0, i), \
		ft_substr(cmd, i + 1, ft_strlen(cmd) - (i + 1)));
	return (cmd);
}

static char	*export_appended(char *line, char *cmd)
{
	int		line_value;
	int		value;
	char	*str;

	line_value = check_envp_value(line);
	value = check_envp_value(cmd);
	if (!line_value)
	{
		str = ft_str_fuse(ft_strjoin(line, "+="), \
					ft_substr(cmd, value + 1, ft_strlen(cmd) - (value + 1)));
		free(line);
	}
	else
		str = ft_str_fuse(line, \
					ft_substr(cmd, value + 1, ft_strlen(cmd) - (value + 1)));
	return (str);
}

static bool	export_targeted(char *cmd, char *target, t_envp *envp, bool append)
{
	while (envp)
	{
		if (!ft_strcmp(target, envp->identifier))
		{
			if (append)
				envp->line = export_appended(envp->line, cmd);
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
