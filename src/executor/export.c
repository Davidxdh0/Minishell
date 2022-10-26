/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 20:08:09 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/26 20:20:17 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**append_env(char **envp, char *variable)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	
	if (!envp)
		return(NULL);
	while(envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 2);
	if (!new_envp)
		return (NULL);
	j = 0;
	while(i < j)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(variable);
	return (new_envp);
}

char	**change_env(char **envp, char *variable, char *change)
{
	
}