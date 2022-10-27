/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 15:26:47 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

/*
	Debug function for showing the information in te line list
*/
// void	show_line_lst(t_line_lst *node)
// {
// 	int	i;

// 	i = 0;
// 	// node = get_first_node(node);
// 	printf("idex\ttype\tvalue\n");
// 	while (node != NULL)
// 	{
// 		printf("%i\t%d\t%s\n", i, node->type, node->value);
// 		node = node->next;
// 		i++;
// 	}
// }

int	amount_of_tokens(char **tokens)
{
	int	list_len;

	list_len = 0;
	tokens =  NULL;
	return (list_len);
}

// /* Add a node after a given node */
// void	insert_node_after(t_line_lst **node)
// {
// 	t_line_lst	*new_node;

// 	if (node == NULL)
// 	{
// 		node = (t_line_lst *)malloc(sizeof(t_line_lst));
// 		(node)->next = NULL;
// 		(node)->prev = NULL;
// 		(node)->type = empty;
// 		(node)->value = "";
// 	}
// 	else
// 	{
// 		new_node = NULL;
// 		new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
// 		(new_node)->next = (node)->next;
// 		(node)->next = new_node;
// 		(new_node)->prev = node;
// 		(new_node)->type = empty;
// 		(new_node)->value = "";
// 	}
// 	// if (node == NULL)
// 	// 	node = (t_line_lst *)malloc(sizeof(t_line_lst));
// 	// else
// 	// 	new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
// 	// if (node == NULL)
// 	// {
// 	// 	node->prev = NULL;
// 	// 	node->next = NULL;
// 	// 	node->type = empty;
// 	// 	node->value = "";
// 	// }
// 	// else
// 	// {
// 	// 	new_node->next = node->next;
// 	// 	node->next = new_node;
// 	// 	new_node->prev = node;
// 	// 	new_node->type = empty;
// 	// 	node->value = "";
// 	// }
// }

// /* Loop to the last node */
// t_line_lst	*get_last_node(t_line_lst *node)
// {
// 	if (node == NULL)
// 		return (NULL);
// 	while (1)
// 	{
// 		if (node->next == NULL)
// 			return (node);
// 		node = node->next;
// 	}
// 	return (node);
// }

// /* Add a node at the end */
// void	add_node_end(t_line_lst **node)
// {
// 	insert_node_after(*get_last_node(&node));
// }

/* Add a node before a given node */
// void	insert_node_before(t_line_lst *node)
// {
// 	t_line_lst	*new_node;

// 	new_node = (t_line_lst *)malloc(sizeof(t_line_lst));
// 	new_node->type = empty;
// 	new_node->value = "";
// 	if (node == NULL)
// 	{
// 		new_node->prev = NULL;
// 		new_node->next = NULL;
// 	}
// 	else
// 	{
// 		new_node->prev = node->prev;
// 		node->prev = new_node;
// 		new_node->next = node;
// 	}
// }

// /* Loop to the first node */
// t_line_lst	*get_first_node(t_line_lst *node)
// {
// 	if (node == NULL)
// 		return (NULL);
// 	while (1)
// 	{
// 		if (node->prev == NULL)
// 			return (node);
// 		node = node->prev;
// 	}
// }

// /* Add a node at the front */
// void	add_node_front(t_line_lst *node)
// {
// 	insert_node_before(get_first_node(node));
// }

// /* Remove given node */
// void	remode_node(t_line_lst *node)
// {
// 	t_line_lst	*temp;

// 	if (node == NULL)
// 		return ;
// 	temp = node;
// 	node->prev->next = node->next;
// 	node->next->prev = node->prev;
// 	free(node);
// }

// /* Remove the list */
// void	remove_list(t_line_lst *node)
// {
// 	t_line_lst	*del;

// 	node = get_first_node(node);
// 	while (node)
// 	{
// 		del = node;
// 		node = node->next;
// 		free(del);
// 	}
// }

// /* Count length of list */
// int		len_of_list(t_line_lst *node)
// {
// 	int			counter;

// 	counter = 0;
// 	while (node)
// 	{
// 		node = node->next;
// 		counter++;
// 	}
// 	return (counter);
// }



void	insert_at_start(t_line_lst **head, int type, char *value)
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

void	show_list(t_line_lst *node)
{
	int			i;

	i = 1;
	printf("index\ttype\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t%s\n" ,i, node->type, node->value);
		node = node->next;
		i++;
	}
}

/* The parser processes the tokens build the list with */
t_line_lst	*parser(char **tokens)
{
	int			len_list;
	t_line_lst	*head;

	len_list = amount_of_tokens(tokens);
	head = NULL;
	insert_at_start(&head, empty, "");
	// show_list(head);
	return (head);
}
