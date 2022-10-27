/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 09:15:31 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 15:22:34 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_tokens(char *line)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (line[index] != '\0')
	{
		if (line[index] == '"' || line[index] == '\'')
			get_data_in_quotes(&line[index]);
		ft_putchar_fd(line[index], 1);
		index++;
		ft_putchar_fd('\n', 1);
	}
	return (counter);
}

/*
	The lexer takes the input line and puts the characters together into words 
	called tokens.
*/
char	**lexer(char *line)
{
	char	**tokens;

	count_tokens(line);
	tokens = NULL;
	// tokens = malloc(sizeof(char *) * count_tokens(line));
	return (tokens);
	// return (ft_split(line, ' '));
}

// void insertStart(struct Node** head, int data){
    
//     // creating memory for newNode
//     struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    
//     // assigning newNode's next as the current head 
//     // Assign data & and make newNode's prev as NULL
//     newNode->data = data;
//     newNode->next = *head;
//     newNode->prev = NULL;
    
//     // if list already had item(s)
//     // We need to make current head previous node as this new node
//     if(*head != NULL)
//         (*head)->prev = newNode;
    
//     // change head to this newNode
//     *head = newNode;
    
// }

// void insertLast(struct Node** head, int data){
//     struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

//     newNode->data = data;
//     newNode->next = NULL;
    
//     //need this if there is no node present in linked list at all
//     if(*head==NULL){
//         *head = newNode;
//         newNode->prev = NULL;
//         return;
//     }
    
//     struct Node* temp = *head;
    
//     // traverse till the last node
//     while(temp->next!=NULL)
//         temp = temp->next;
    
//     // assign last node's next to this new Node
//     temp->next = newNode;
//     // assign this new Node's previous to last node(temp)
//     newNode->prev = temp;
// }

// void display(struct Node* node)
// {
//     struct Node* end;
//     printf("\nIn Forward Direction\n");
//     while (node != NULL) {
//         printf(" %d ", node->data);
//         end = node;
//         node = node->next;
//     }
 
//     printf("\nIn Backward direction \n");
//     while (end != NULL) {
//         printf(" %d ", end->data);
//         end = end->prev;
//     }
// }