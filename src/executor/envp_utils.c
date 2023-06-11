/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 15:00:41 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/05 15:00:43 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	check_envp_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

bool	increase_shlvl(t_envp *envp)
{
	char	*tmp;
	int		atoi;

	while (envp)
	{
		if (!ft_strcmp("SHLVL", envp->identifier))
		{
			tmp = envp->string;
			atoi = ft_atoi(envp->string);
			envp->string = ft_itoa(atoi + 1);
			free(tmp);
			free(envp->line);
			envp->line = ft_strjoin("SHLVL=", envp->string);
			return (true);
		}
		envp = envp->next;
	}
	return (false);
}

/*
void	show_envp_node(t_envp *envp)
{
	if (envp)
		printf("Line: %s\nIdentifier: %s\tString: %s\n", envp->line,
		envp->identifier, envp->string);
}
void	show_envp_struct(t_envp *envp)
{
	int	i;

	i = 1;
	while (envp)
	{
		printf("Node #%d\nLine:\t\t%s\nIdentifier:\t%s\nString:\t\t%s\n\n", i,
			envp->line, envp->identifier, envp->string);
		envp = envp->next;
		i++;
	}
}
	*/