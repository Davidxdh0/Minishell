/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/31 18:05:20 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char	*expand_var(char* value, char** envp) 
{
	if (value[1] == '?')
		return (value = ft_strdup(ft_itoa(g_exitcode)));
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

char	*expand_word(char* value, char** envp) 
{
	int i;
	int begin;
	int count;
	i = 0;
	begin = 0;
	count = 0;
	//count aantal expands
	printf("ervoor count = %d\n", count);
	count = count_words_expander(value);
	printf("erna count = %d\n", count);
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
			value = ft_strdup(change_str(value, begin, i, envp, count));
			count--;
		}
		// if (value[i] != '\0' || value[i] != '?')
		// 	i++;
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

char *change_str(char *str, int begin, int eind, char **envp, int count)
{
	int len;
	char *newstr;
	char *env;
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
	str = ft_strdup(create_and_fill_string(str, begin, eind, env, len));

	count++;
	printf("change str newstr = %s\n", str);
	return (0);
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
		
		if (find_variable(temp->value))
		{
			printf("count = \n");
			if (temp->type == e_var)
				temp->value = ft_strdup(expand_var(temp->value, envp));
			else if (temp->state == 2 || temp->state == 0)
				temp->value = ft_strdup(expand_word(temp->value, envp)); // count expands - elk command expanden
			temp->state = temp->state;
		}
		temp = temp->next;
	}
	return line;
}
