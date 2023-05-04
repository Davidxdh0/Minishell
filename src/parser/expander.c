/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/04 20:12:45 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_line_lst	*expander(t_line_lst *line_lst)
{
	t_line_lst *temp;
	// t_line_lst *temps;
	char *tempstring;
	
	temp = line_lst;
	while (line_lst != NULL)
	{
		tempstring = ft_strdup(line_lst->value);
		// printf("value = %s\ttype = %d en state = %d\n", line_lst->value, line_lst->type, line_lst->state);
		if (line_lst != NULL && line_lst->state > 0)
		{
			// printf("value = %s\n", line_lst->value);
			line_lst = word_list(line_lst);
			// if (line_lst->next != NULL)
			// 	printf("current = %s, next = %s\n", line_lst->value, line_lst->next->value);
			if (line_lst->next != NULL && line_lst->next->type == e_whitespace && line_lst->next->state == 0 && line_lst->next->next != NULL)
			{
				line_lst->next = line_lst->next->next;
			}
		}
		
		else if (line_lst->type == e_whitespace && line_lst->state == 0)
		{
			// printf("prev = %s\tcurrent = %s, next = %s\n", line_lst->prev->value, line_lst->value, line_lst->next->value);
			line_lst = whitespaces_list(line_lst);
			if (line_lst->prev == NULL) // check if it's the head node
			{
				temp = line_lst->next;
				free(line_lst);
				line_lst = temp;
				// continue; // skip to the next node
			}
			// printf("type= %d en state = %d\n", line_lst->type, line_lst->state);
			line_lst->value = ft_strjoin(line_lst->value, "-----------------");
			
			line_lst->prev->next = line_lst->next;
			// printf("last = %s\n", line_lst->value);
		}
		if (line_lst != NULL)
			line_lst = line_lst->next;
	}
	return (temp);
}

t_line_lst	*word_list(t_line_lst *line)
{
	t_line_lst *temp;
	temp = line;
	char *str;
	int i = 0;
	
	str = "";
	while (temp != NULL && temp->state > 0)
	{
		// printf("tempvalue = %s en str = %s\n", temp->value, str);
		str = ft_strjoin(str, temp->value);
		temp = temp->next;
		i++;
	}
	// // free(line->value);
	line->value = NULL;
	line->value = ft_strdup(str);
	// if (line->value)
	// 	line->type = e_word;
	// i = ft_strlen(line->value);
	// if (i > 1 && line->value[0] == '\"' && line->value[i - 1] == '\"')
	// 	line->value = ft_substr(line->value, 1, i - 2);
	line->next = temp;
	return (line);
}

t_line_lst	*whitespaces_list(t_line_lst *line)
{
	t_line_lst *temp;
	temp = line;

	int i = 0;
	while (temp != NULL && temp->type == e_whitespace && temp->state == 0)
	{
		temp = temp->next;
		i++;
	}
	line->next = temp;
	return (line);
}

// char	*ft_getenv(const char *name, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (name[j] == envp[i][j])
// 		{
// 			j++;
// 			if (!name[j])
// 				return (envp[i] + j);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

int find_variable(char *str)
{
	int i;
	i = 0;

	while(str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$' | str[i + 1] == '?' )
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
	// printf("newstr = %s\n", newstr);
	newstr[i] = '\0';
	return (newstr);
}

t_line_lst	*variable_expand(t_line_lst *line, char **envp)
{
	t_line_lst *temp;
	int i;
	// char *str;
	int begin;
	// int len;
	char *str;

	begin = 0;
	i = 0;
	temp = line;
	while (temp != NULL)
	{
		if (find_variable(temp->value))
		{
			if (temp->type == e_var)
			{
				temp->value = ft_substr(temp->value, 1, ft_strlen(temp->value));
				str = ft_getenv(temp->value, envp);
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

// t_line_lst	*lookup_env(t_line_lst *line)
// {
// 	t_line_lst *temp;
// 	temp = line;

// 	int i = 0;
// 	while (temp != NULL)
// 	{
// 		if (temp->type == e_quote && temp->state == 2)
// 		{
// 			while (temp->value[i])
// 			{
// 				if (temp->value[i] == '$')
// 				{
// 					if (temp->value[i+1])
// 						;
// 				}
						
// 			}

// 		}
// 		temp = temp->next;
// 	}
// 	line->next = temp;
// 	return (line);
// }