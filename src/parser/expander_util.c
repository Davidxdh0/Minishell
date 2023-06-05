/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 20:04:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/01 20:24:39 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	*get_new_env(char *value, t_envp *envp)
{
	while (envp != NULL)
	{
		if (!ft_strcmp(value, envp->identifier))
			return (envp->string);
		envp = envp->next;
	}
	return (NULL);
}

int	count_words_expander(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = -1;
	while (value[i] != '\0')
	{
		while (value[i] == '$')
			i++;
		if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			while (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
				i++;
			count++;
		}
		if (value[i] != '\0')
			i++;
	}
	return (count);
}

int	find_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strlen(str) > 1)
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}
