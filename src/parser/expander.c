/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/12 13:52:35 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"


char	*ft_getenv(const char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (name[j] == envp[i][j])
		{
			j++;
			if (!name[j])
				return (envp[i] + j);
		}
		i++;
	}
	return (NULL);
}

int find_variable(char *str)
{
	int i;
	
	i = 0;
	while(str[i] && ft_strlen(str) > 1)
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$' || str[i + 1] == '?' )
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

char *change_str(char *str, int begin, int eind, char **envp)
{
	int len;
	char *newstr;
	char *env;
	
	int i = 0;
	int k = 0;
	// printf("str = %s", str);
	len = ft_strlen(str);
	
	env = ft_substr(str, begin + 1, eind - begin - 1);
	len -= (ft_strlen(env));
	// printf("str = %s, len = %d begin %d eind %d env = %s\n",str, len, begin, eind, env);
	env = ft_getenv(env, envp);
	// if (!env)
	// 	return ("");
	// printf("str = %s, len = %d begin %d eind %d env = %s\n",str, len, begin, eind, env);
	env = ft_substr(env, 1, ft_strlen(env));
	len += ft_strlen(env);
	newstr = malloc(sizeof(char *) * len + 1);
	// printf("total lengte %d begin = %d, eind = %d\n", len, begin, eind);
	while (i < len)
	{
		while (i < begin)
		{
			newstr[i] = str[i];
			// printf("new[%d] = %c\n", i, newstr[i]);
			i++;
		}
		while (begin <= i && begin <= eind)
		{
			
			// printf("env[%d] = %c en i = %d\n", k, env[k], i);
			newstr[i] = env[k];
			// printf("new[%d] = %c\n", i, newstr[i]);
			k++;
			begin++;
			i++;
		}
		// printf("str[%d] = %c\n", i, str[i]);
		newstr[i] = str[i-1];
		// printf("new[%d] = %c\n", i, newstr[i]);
		i++;
	}
	// printf("env = %s\n", env);
	newstr[i] = '\0';
	printf("newstr = %s\n", newstr);
	return (newstr);
}

t_line_lst	*variable_expand(t_line_lst *line, char **envp)
{
	t_line_lst *temp;
	int i;
	int begin;
	char *str;

	begin = 0;
	i = 0;
	temp = line;
	while (temp != NULL)
	{
		// printf("var = %s\n", temp->value);
		if (find_variable(temp->value))
		{
			// printf("dollar sign found = %s\n", temp->value);
			if (temp->type == e_var)
			{
				temp->value = ft_substr(temp->value, 1, ft_strlen(temp->value));
		
				printf("dsgsd %s\n", temp->value);
				str = ft_getenv(temp->value, envp);
				if (!str)
				{
					str = ft_strdup("");
					temp->value = str;
				}
				else
					str = ft_substr(str, 1, ft_strlen(str));
					temp->value = str;
			}
			else if (temp->state == 2 || temp->state == 0)
			{
				while(temp->value[i] != '$')
					i++;
				begin = i;
				i++;
				while(ft_isalpha(temp->value[i]))
					i++;
				temp->value = change_str(temp->value, begin, i, envp);
				
				
				//stop in string
			}
		}
		temp = temp->next;
	}
	return (line);
}
