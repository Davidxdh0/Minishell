/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 18:38:09 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	*expand_var(char *value, t_envp *new_envp, int state)
{
	char	*str;

	if (value[1] == '?')
		return (ft_itoa(g_exitcode));
	value = ft_substr(value, 1, ft_strlen(value));
	str = get_new_env(value, new_envp);
	free(value);
	if (!str)
		return (ft_strdup(""));
	else
	{
		if (state == 2)
			str = expand_spaces(str);
		return (ft_strdup(str));
	}
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
			return (ft_itoa(g_exitcode));
		else if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			begin = i;
			while (ft_isascii(value[i]) && value[i] != '$')
				i++;
			value = change_str(value, begin, i, new_envp);
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
	newstr = ft_malloc(len + 1);
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
	char	*envhold;

	len = ft_strlen(str);
	env = ft_substr(str, begin, eind - begin - 1);
	len -= (ft_strlen(env));
	envhold = env;
	env = get_new_env(env, envp);
	free(envhold);
	if (!env)
		return (ft_strdup(""));
	env = ft_substr(env, 1, ft_strlen(env));
	len += ft_strlen(env);
	str = fill_string(str, begin, eind, env);
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
				str = expand_var(temp->value, new_envp, temp->state);
			else if (temp->state == 2 || temp->state == 0)
				str = expand_word(temp->value, new_envp);
			else
				str = NULL;
			if (str != NULL)
			{
				free(temp->value);
				temp->value = str;
			}
			temp->state = temp->state;
		}
		temp = temp->next;
	}
	return (line);
}
