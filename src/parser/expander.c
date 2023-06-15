/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/15 16:42:04 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	*expand_var(char *value, t_envp *new_envp)
{
	char	*str;

	if (value[1] == '?')
	{
		value = ft_itoa(g_exitcode);
		return (value);
	}
	value = ft_substr(value, 1, ft_strlen(value));
	str = get_new_env(value, new_envp);
	if (!str)
	{
		free(value);
		value = ft_strdup("");
	}
	else
	{
		free(value);
		value = ft_strdup(str);
	}
	return (value);
}

char	*expand_word(char*value, t_envp *new_envp)
{
	int	i;
	int	begin;
	int	count;

	i = 0;
	count = count_words_expander(value);
	while (count >= 0 && value[i] != '\0')
	{
		while (value[i] == '$')
			i++;
		if (value[i] != '\0' && value[i] == '?')
			return (value = ft_strdup(ft_itoa(g_exitcode)));
		else if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			begin = i;
			while (ft_isascii(value[i]) && value[i] != '$')
				i++;
			value = ft_strdup(change_str(value, begin, i, new_envp));
			count--;
		}
	}
	return (value);
}

char	*fill_string(char *str, int bgn, int end, char *env)
{
	char	*newstr;
	int		i;
	int		k;
	int		len;

	len = bgn + ft_strlen(env) + ft_strlen(str + end) + 1;
	i = 0;
	k = 0;
	newstr = malloc(len + 1);
	while (i < bgn)
	{
		newstr[i] = str[i];
		i++;
	}
	while (bgn <= i && bgn <= end)
	{
		newstr[i] = env[k];
		k++;
		bgn++;
		i++;
	}
	newstr[i] = str[i - 1];
	i++;
	newstr[i] = '\0';
	return (newstr);
}

char	*change_str(char *str, int begin, int eind, t_envp *envp)
{
	int		len;
	char	*env;

	len = ft_strlen(str);
	env = ft_substr(str, begin, eind - begin - 1);
	printf("str = %s, env = %s\n", str, env);
	len -= (ft_strlen(env));
	env = get_new_env(env, envp);
	printf("str = %s, env = %s\n", str, env);
	if (!env)
		return ("");
	env = ft_substr(env, 1, ft_strlen(env));
	len += ft_strlen(env);
	str = ft_strdup(fill_string(str, begin, eind, env));
	free(env);
	return (str);
}

t_line_lst	*variable_expand(t_line_lst *line, t_envp *new_envp)
{
	t_line_lst	*temp;
	char		*str;

	temp = line;
	while (temp != NULL)
	{
		if (find_variable(temp->value))
		{
			if (temp->type == e_var && temp->state != 1)
				str = expand_var(temp->value, new_envp);
			else if (temp->state == 2 || temp->state == 0)
				str = expand_word(temp->value, new_envp);
			else
				str = NULL;
			if (str != NULL)
			{
				free(temp->value);
				temp->value = ft_strdup(str);
				free(str);
			}
			temp->state = temp->state;
		}
		temp = temp->next;
	}
	return (line);
}
