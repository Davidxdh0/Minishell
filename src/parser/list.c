/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:11 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/10 13:23:38 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp for show_t_list function 

char	*type_to_string(note_type type)
{
	if (type == e_start)
		return ("start\t");
	if (type == e_cmd)
		return ("cmd\t");
	if (type == e_file)
		return ("file\t");
	if (type == e_pipe)
		return ("pipe\t");
	if (type == e_word)
		return ("word\t");
	if (type == e_quote)
		return ("quote\t");
	if (type == e_dquote)
		return ("dquote\t");
	if (type == e_whitespace)
		return ("wspace\t");
	if (type == e_var)
		return ("var\t");
	if (type == e_redirect_i)
		return ("redirect_i");
	if (type == e_redirect_o)
		return ("redirect_o");
	if (type == e_delimiter)
		return ("delimiter");
	if (type == e_append)
		return ("append\t");
	return ("no type");
}

void	show_t_list(t_line_lst *node, char *input_line)
{
	int	i;

	i = 1;
	
	printf("\ninput_line = %s", input_line);
	printf("\n---------- line list table -----------\n");
	printf("index\ttype\tlen\ttype_name\tstate\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t%d\t%s\t%d\t%s\n", i, node->type, node->len,
			type_to_string(node->type), (int)node->state, node->value);
		// if (node->next == NULL) {
		// 	printf("Next pointer of node %d is NULL\n", i);
		// }
		// if (node->prev == NULL) {
		// 	printf("Prev pointer of node %d is NULL\n", i);
		// }
		node = node->next;
		i++;
	}
	printf("-------- end line list table ---------\n\n");
}


void	delete_t_list(t_line_lst **head)
{
	t_line_lst	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void	add_at_end_of_list(t_line_lst **head, int type, char *value, int state)
{
	t_line_lst	*new_node;
	t_line_lst	*temp;

	new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
	new_node->next = NULL;
	new_node->type = type;
	new_node->value = ft_strdup(value);
	new_node->len = ft_strlen(value);
	new_node->state = state;
	if (*head == NULL)
	{
		*head = new_node;
		new_node->prev = NULL;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

int	length_of_list(t_line_lst *node)
{
	int	lenght;

	lenght = 0;
	while (node != NULL)
	{
		node = node->next;
		lenght++;
	}
	return (lenght);
}
