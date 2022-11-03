/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/03 12:17:54 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>	// temp

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

void	show_t_list(t_line_lst *node)
{
	int	i;

	i = 1;
	printf("\n------ line list table -------\n");
	printf("index\ttype\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t\"%s\"\n" ,i, node->type, node->value);
		node = node->next;
		i++;
	}
	printf("---- end line list table -----\n\n");
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

void	test_list(void)
{
	t_line_lst	*head;

	head = NULL;
	add_at_end_of_list(&head, e_cmd, "ls -la");
	add_at_end_of_list(&head, e_pipe, "|");
	add_at_end_of_list(&head, e_cmd, "grep Nov");
	add_at_end_of_list(&head, e_pipe, "|");
	add_at_end_of_list(&head, e_cmd, "grep m");
	show_t_list(head);
	delete_t_list(&head);
}

int	amount_of_tokens(char **tokens)
{
	int	list_len;

	list_len = 0;
	while (tokens[list_len])
		list_len++;
	return (list_len);
}

/* Note
Option 1: [ ]
	lexer checkt the grammar (BNF) and detects tokens (a group of caracters).
	parser checkt grammer (BNF) and create the type of the token and stors it in a list.

Option 2: [ ]
	lexer chect the grammer (BNF), detekt tokens and type of tokens.
	parser stores tokens en the type of tokens in a list.

Option 3: [X]
	use lexer inside of the parser
	
Handle in the parser:
	Variables and Parameters
	
Word Expansions: After parsing, but before execution. example $OSTYPE = darwin18.0
*/

char	**test_token_array(void)
{
	int		amount_of_tokens;
	char	**tokens;

	amount_of_tokens = 5;
	tokens = (char **)malloc(sizeof(char *) * (amount_of_tokens + 1));
	tokens[0] = ft_strdup("ls -la");
	tokens[1] = ft_strdup("|");
	tokens[2] = ft_strdup("grep Nov");
	tokens[3] = ft_strdup("|");
	tokens[4] = ft_strdup("grep m");
	tokens[5] = NULL;
	return (tokens);
}

int		is_word(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (ft_isdigit(c))
		return (1);
	// if (c == '')
	return (0);
}

t_line_lst	*fil_list(char *line)
{
	t_line_lst	*head;
	int			i;
	int			len;

	i = 0;
	head = NULL;
	line = ft_strtrim(line, " ");
	while (line[i])
	{
		if (ft_isalpha(line[i]))	// command, word or filename. Use the previous type to check the grammer
		{
			len = 0;
			while (ft_isalpha(line[ i + len]))
				len++;
			add_at_end_of_list(&head, e_cmd, ft_substr(line, i, len));
			i += len - 1;
		}
		if (line[i] == '|')
			add_at_end_of_list(&head, e_pipe, "|");
		if (line[i] == '<')
		{
			i++; 
			if (line[i] != '<')
			{
				add_at_end_of_list(&head, e_redirect_I, "<");
				continue;
			}
			add_at_end_of_list(&head, e_delimiter, "<<");
		}	
		if (line[i] == '>')
		{
			i++;
			if (line[i] != '>')
			{
				add_at_end_of_list(&head, e_redirect_O, ">");
				continue;
			}	
			add_at_end_of_list(&head, e_append, ">>");
		}
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
			{
				add_at_end_of_list(&head, e_var, "$?");
				i++;
				continue;
			}
			if (line[i] == '$')
			{
				add_at_end_of_list(&head, e_var, "$$");
				i++;
				continue;
			}	
			len = 0;
			while (is_word(line[i + len]))
				len++;
			add_at_end_of_list(&head, e_var, ft_substr(line, i, len));
			i += len - 1;
		}
		i++;
	}
	return (head);
}

// adlskjsdf$?asdfjkasl

t_line_lst	*parser(char *line)
{
	t_line_lst	*head;

	head = fil_list(line);
	return (head);
}
