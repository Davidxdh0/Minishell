/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 20:04:47 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/20 20:23:47 by dyeboa        ########   odam.nl         */
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

void	expand_heredoc_word(char *value, t_envp *new_envp, int fd)
{
	int	i;
	int	begin;

	i = 0;
	while (value[i] != '\0')
	{
		while (value[i] != '\0' && value[i] != '$')
		{
			write(fd, &value[i], 1);
			i++;
		}
		if (value[i] != '\0' && value[i] == '$')
			i++;
		if (value[i] != '\0' && value[i] == '?' && i++ > 0)
			putstrherdoc(fd);
		else if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			begin = i;
			while (value[i] != '\0' && ft_isascii(value[i]) && \
			value[i] != '$' && value[i] != ' ')
				i++;
			ft_putstr_fd(change_heredoc_str(value, begin, i, new_envp), fd);
		}
	}
}

char	*change_heredoc_str(char *str, int begin, int eind, t_envp *envp)
{
	int		len;
	char	*env;
	char	*envhold;
	
	len = ft_strlen(str);
	env = ft_substr(str, begin, eind - begin);
	len -= (ft_strlen(env));
	envhold = env;
	env = get_new_env(env, envp);
	free(envhold);
	if (!env)
		return ("");
	return (env);
}
