/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/20 14:20:41 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_line_lst	*expander(t_line_lst *line_lst)
{
	t_line_lst *temp;
	char *tempstring;
	
	temp = line_lst;
	while (line_lst != NULL)
	{
		tempstring = ft_strdup(line_lst->value);
		if (line_lst->type == e_whitespace && line_lst->state == 0)
		{
			// printf("next");
			line_lst->prev->next = line_lst->next;
		}
		else if (line_lst != NULL && line_lst->state > 0)
		{
			// printf("value = %s\n", line_lst->value);
			line_lst = word_list(line_lst);
		}
		if (line_lst != NULL)
			line_lst = line_lst->next;
	}
	// printf("string = %s\n", tempstring);
	return (temp);
}

t_line_lst	*word_list(t_line_lst *line)
{
	t_line_lst *temp;
	temp = line;
	char *str;
	int i = 0;
	while (temp != NULL && temp->state > 0)
	{
		printf("tempvalue = %s en str = %s\n", temp->value, str);
		str = ft_strjoin(str, temp->value);
		temp = temp->next;
		i++;
	}

	// // free(line->value);
	line->value = NULL;
	line->value = ft_strdup(str);
	line->next = temp;
	return (line);
}