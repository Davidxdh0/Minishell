/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/03 13:09:14 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>	// temp
#include "../main/main.h"

int	amount_of_tokens(char **tokens)
{
	int	list_len;

	list_len = 0;
	tokens =  NULL;
	return (list_len);
}

void	delete_list(t_line_lst **head)
{
	t_line_lst	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void	add_at_start_of_list(t_line_lst **head, int type, char *value)
{
	t_line_lst	*new_node;

	new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
	new_node->prev = NULL;
	new_node->next = *head;
	new_node->type = type;
	new_node->value = value;
	if (*head != NULL)
		(*head)->prev = new_node;
	*head = new_node;
}

void	add_at_end_of_list(t_line_lst **head, int type, char *value)
{
	t_line_lst	*new_node;
	t_line_lst	*temp;

	new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
	new_node->next = NULL;
	new_node->type = type;
	new_node->value = value;
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

void	show_list(t_line_lst *node)
{
	int	i;

	i = 1;
	printf("index\ttype\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t%s\n" ,i, node->type, node->value);
		node = node->next;
		i++;
	}
	printf("\n");
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

void	test_list(t_line_lst *head, char **envp)
{
	t_data	data;

	data.envp = envp;
	head = NULL;
	add_at_end_of_list(&head, e_cmd, "ls -la");
	add_at_end_of_list(&head, e_cmd, "grep Nov");
	add_at_end_of_list(&head, e_cmd, "grep obj");
	//add_at_end_of_list(&head, e_file, "outfile.txt");
	show_list(head);
	printf("length of list is %d\n", length_of_list(head));
	execute_cmd_list(head, &data);
	//delete_list(&head);
	//show_list(head);
	//printf("length of list is %d\n", length_of_list(head));
}

t_line_lst	*parser(t_line_lst *head, char **tokens)
{
	int			len_list;

	len_list = amount_of_tokens(tokens);
	return (head);
}
