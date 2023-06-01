/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/01 16:56:04 by dyeboa        ########   odam.nl         */
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

char	*expand_var(char* value, t_envp* new_envp) 
{
	char *str;
	
	if (value[1] == '?')
		return (value = ft_strdup(ft_itoa(g_exitcode)));
	value = ft_substr(value, 1, ft_strlen(value));
	str = get_new_env(value, new_envp);
	if (!str) 
	{
		str = ft_strdup("");
		value = str;
	}
	else 
	{
		str = ft_substr(str, 0, ft_strlen(str));
		value = ft_strdup(str);
	}
	free(str);
	return (value);
}

int		count_words_expander(char *value)
{
	int i;
	int count;

	i = 0;
	count = -1;
	while (value[i] != '\0')
	{
		while (value[i] == '$')
			i++;
		if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			while (value[i] != '\0' &&ft_isascii(value[i]) && value[i] != '$')
				i++;
			count++;
		}
		if (value[i] != '\0')
			i++;
	}
	return (count);
}

char	*expand_word(char* value, t_envp *new_envp) 
{
	int i;
	int begin;
	int count;

	i = 0;
	count = count_words_expander(value);
	while (count > 0 && value[i] != '\0')
	{
		while (value[i] == '$')
			i++;
		if (value[i] != '\0' && value[i] == '?')
		{
			g_exitcode = 5;
			return (value = ft_strdup(ft_itoa(g_exitcode)));
		}
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

int find_variable(char *str)
{
	int i;
	
	i = 0;
	while(str[i] && ft_strlen(str) > 1)
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char *create_and_fill_string(char *str, int begin, int eind, char *env, int len)
{
	int i;
	int k;
	char *newstr;
	
	i = 0;
	k = 0;
	newstr = malloc(sizeof(char *) * len + 1);
	while (i < len)
	{
		while (i < begin)
		{
			newstr[i] = str[i];
			i++;
		}
		while (begin <= i && begin <= eind)
		{
			newstr[i] = env[k];
			k++;
			begin++;
			i++;
		}
		newstr[i] = str[i-1];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char *change_str(char *str, int begin, int eind, t_envp* envp)
{
	int len;
	char *env;
	
	len = ft_strlen(str);
	env = ft_substr(str, begin + 1, eind - begin - 1);
	len -= (ft_strlen(env));
	env = get_new_env(env, envp);
	if (!env)
		return ("");
	env = ft_substr(env, 1, ft_strlen(env));
	len += ft_strlen(env);
	str = ft_strdup(create_and_fill_string(str, begin, eind, env, len));
	return (str);
}

t_line_lst	*variable_expand(t_line_lst *line, t_envp *new_envp)
{
	t_line_lst *temp;
	int i;
	int begin;

	begin = 0;
	i = 0;
	temp = line;
	while (temp != NULL)
	{
		if (find_variable(temp->value))
		{
			printf("count = \n");
			if (temp->type == e_var)
				temp->value = ft_strdup(expand_var(temp->value, new_envp));
			else if (temp->state == 2 || temp->state == 0)
				temp->value = ft_strdup(expand_word(temp->value, new_envp)); // count expands - elk command expanden
			temp->state = temp->state;
		}
		temp = temp->next;
	}
	return line;
}
