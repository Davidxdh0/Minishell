/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/30 15:43:36 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	*expand_var(char* value, char** envp) 
{
	value = ft_substr(value, 1, ft_strlen(value));
	char *str = ft_getenv(value, envp);
	if (!str) 
	{
		str = ft_strdup("");
		value = str;
	}
	else 
	{
		str = ft_substr(str, 1, ft_strlen(str));
		value = ft_strdup(str);
	}
	free(str);
	return (value);
}

char	*expand_word(char* value, char** envp) 
{
	int i;
	int begin;
	int count;
	char **array;
	i = 0;
	begin = 0;
	count = 0;
	//count aantal expands
	while (value[i] != '\0')
	{
		while (value[i] == '$')
			i++;
		if (value[i] != '\0' && ft_isascii(value[i]) && value[i] != '$')
		{
			while (ft_isascii(value[i]) && value[i] != '$')
				i++;
			count++;
		}
	}
	value = change_str(value, begin, i, count);
	return (value);
	begin = i;
	i++;
	while (ft_isalpha(value[i]))
		i++;
	// $$$$$USER$?test
	// $$$$$dyeboa0test
	value = change_str(value, begin, i, envp);
	// stop in string
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

char *change_str(char *str, int begin, int eind, char **envp, int count)
{
	int len;
	char *newstr;
	char *env;
	char **array;
	int i = 0;
	int k = 0;
	array = (char **)malloc(sizeof(char **) * count + 1);
	// printf("str = %s", str);
	len = ft_strlen(str);
	env = ft_substr(str, begin + 1, eind - begin - 1);
	len -= (ft_strlen(env));
	env = ft_getenv(env, envp);
	if (!env)
		return ("");
	// printf("str = %s, len = %d begin %d eind %d env = %s\n",str, len, begin, eind, env);
	env = ft_substr(env, 1, ft_strlen(env));
	len += ft_strlen(env);
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
	// printf("newstr = %s\n", newstr);
	return (newstr);
}

t_line_lst	*variable_expand(t_line_lst *line, char **envp)
{
	t_line_lst *temp;
	int i;
	int begin;

	begin = 0;
	i = 0;
	temp = line;
	while (temp != NULL)
	{
		// find $ teken - zo ja expand
		// if evar - substring alles na $.
		if (find_variable(temp->value))
		{
			if (temp->type == e_var)
				temp->value = ft_strdup(expand_var(temp->value, envp));
			else if (temp->state == 2 || temp->state == 0)
				temp->value = ft_strdup(expand_word(temp->value, envp));
		}
		temp = temp->next;
	}
	return line;
}
