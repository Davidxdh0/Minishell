/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:23 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/12 16:53:07 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>

// Update the next node's "prev" pointer
// Free the memory used by the node
// free(node_to_delete);
// Update the previous node's "next" pointer

void	delete_node(t_line_lst *node_to_delete)
{
	if (node_to_delete == NULL) 
		return ;
    if (node_to_delete->next != NULL)
        node_to_delete->next->prev = node_to_delete->prev;
	if (node_to_delete->prev != NULL)
		node_to_delete->prev->next = node_to_delete->next;
}

note_type	get_last_type(t_line_lst *node)
{
	note_type	type;

	type = e_start;
	while (node != NULL)
	{
		type = node->type;
		if (node->type == e_whitespace && node->prev != NULL)
		{
			node = node->prev;
			type = node->type;
			node = node->next;
		}
		node = node->next;
	}
	return (type);
}

t_line_lst	*parser(char *line)
{
	int				i;
	int				state;
	t_line_lst		*line_lst;

	i = 0;
	state = 0;
	line_lst = NULL;
	while (line[i])
	{
		if (!ft_isspecial(line[i]))
			i += word_case(&line_lst, line + i, state);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			state = quotes(line_lst, line[i], state);
			i++;
		}
		else if (line[i] == '|')
			i += pipe_case(&line_lst, state);
		else if (line[i] == '<')
			i += less_than_case(&line_lst, &line[i], state);
		else if (line[i] == '>')
			i += greater_than_case(&line_lst, &line[i], state);
		else if (line[i] == '$')
			i += dolar_sign_case(&line_lst, &line[i], state);
		else if (ft_isspace(line[i]))
			i += space_case(&line_lst, state);
		else
			i++;
	}
	return (line_lst);
}

t_line_lst	*remove_whitespace_list(t_line_lst *line_lst)
{
	t_line_lst *temp;
	char *tempstring;
	
	temp = line_lst;
	while (line_lst != NULL)
	{
		tempstring = ft_strdup(line_lst->value);
		// printf("value = %s\ttype = %d en state = %d\n", line_lst->value, line_lst->type, line_lst->state);
		if (line_lst->type == e_whitespace && line_lst->state == 0)
		{
			// printf("prev = %s\tcurrent = %s\n", line_lst->prev->value, line_lst->value);
			line_lst = whitespaces_list(line_lst);
			if (line_lst->prev == NULL && line_lst->next != NULL) // check if it's the head node
			{
				temp = line_lst->next;
				free(line_lst);
				line_lst = temp;
				// continue; // skip to the next node
			}
			// printf("type= %d en state = %d\n", line_lst->type, line_lst->state);
			// line_lst->value = ft_strjoin(line_lst->value, "-----------------");
			// delete_node(line_lst);
			if (line_lst->next != NULL)
				line_lst->prev->next = line_lst->next;
		}
		else if (line_lst != NULL && line_lst->state > 0)
		{
			// printf("value = %s\n", line_lst->value);
			line_lst = word_list(line_lst);
			// if (line_lst->next != NULL)
			// 	printf("current = %s, next = %s\n", line_lst->value, line_lst->next->value);
			// if (line_lst->next != NULL && line_lst->next->type == e_whitespace && line_lst->next->state == 0 && line_lst->next->next != NULL)
			// {
			// 	line_lst->next = line_lst->next->next;
			// }
		}
		if (line_lst != NULL)
			line_lst = line_lst->next;
		
	}
	return (temp);
}

t_line_lst	*word_list(t_line_lst *line)
{
	t_line_lst *temp;
	char *str;
	
	int i = 0;
	temp = line;
	str = "";
	while (temp != NULL && temp->state > 0)
	{
		str = ft_strjoin(str, temp->value);
		temp = temp->next;
		free(temp);
		i++;
	}
	line->value = NULL;
	line->value = ft_strdup(str);
	// line->type = e_word;
	// line->state = 0;
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

// t_line_lst *string_quotes(t_line_lst *line_lst)
// {
// 	t_line_lst *temp;
// 	char *tempstring;
	
// 	temp = line_lst;
// 	while (line_lst != NULL)
// 	{
// 		tempstring = ft_strdup(line_lst->value);
// 		if (line_lst != NULL && line_lst->state > 0)
// 		{
// 			// printf("value = %s\n", line_lst->value);
// 			line_lst = word_list(line_lst);
// 			// if (line_lst->next != NULL)
// 			// 	printf("current = %s, next = %s\n", line_lst->value, line_lst->next->value);
// 			// if (line_lst->next != NULL && line_lst->next->type == e_whitespace && line_lst->next->state == 0 && line_lst->next->next != NULL)
// 			// {
// 			// 	line_lst->next = line_lst->next->next;
// 			// }
// 		}
// 		if (line_lst != NULL)
// 			line_lst = line_lst->next;
// 	}
// }