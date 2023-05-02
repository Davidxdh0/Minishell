/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/02 15:19:15 by dyeboa        ########   odam.nl         */
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
	if (line->value)
		line->type = e_word;
	i = ft_strlen(line->value);
	if (i > 1 && line->value[0] == '\"' && line->value[i - 1] == '\"')
		line->value = ft_substr(line->value, 1, i - 2);
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
// 				if (temp->value[i] == "$")
// 				{
// 					if (temp->value[i+1])
// 				}
						
// 			}

// 		}
// 		temp = temp->next;
// 	}
// 	line->next = temp;
// 	return (line);
// }