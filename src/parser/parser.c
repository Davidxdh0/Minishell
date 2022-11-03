/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/11/03 20:39:00 by bprovoos      ########   odam.nl         */
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
	
	printf("\ninput_line = \"%s\"", input_line);
	printf("\n------ line list table -------\n");
	printf("index\ttype\ttype_name\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t%s\t\"%s\"\n" ,i, node->type, \
			type_to_string(node->type), node->value);
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
	show_t_list(head, "");
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
	if (c == '-')
		return (1);
	return (0);
}

note_type	get_last_type(t_line_lst *node)
{
	note_type	type;

	type = e_start;
	while (node != NULL)
	{
		type = node->type;
		node = node->next;
	}
	return (type);
}

int	is_valid_cmd(note_type last_type)
{
	if (last_type == e_start)
		return (1);
	if (last_type == e_pipe)
		return (1);
	return (0);
}

int	is_valid_pipe(note_type last_type)
{
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_file(note_type last_type)
{
	if (last_type == e_redirect_i)
		return (1);
	if (last_type == e_redirect_o)
		return (1);
	if (last_type == e_delimiter)
		return (1);
	if (last_type == e_append)
		return (1);
	return (0);
}

int	is_valid_word(note_type last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	if (last_type == e_var)
		return (1);
	return (0);
}

int	is_valid_var(note_type last_type)
{
	if (last_type == e_cmd)
		return (1);
	if (last_type == e_word)
		return (1);
	return (0);
}

int	is_valid_type(note_type type, t_line_lst *node)
{
	note_type	last_type;

	last_type = get_last_type(node);
	if (type == e_cmd)
		return (is_valid_cmd(last_type));
	if (type == e_file)
		return (is_valid_file(last_type));
	if (type == e_pipe)
		return (is_valid_pipe(last_type));
	if (type == e_word)
		return (is_valid_word(last_type));
	if (type == e_var)
		return (is_valid_var(last_type));
	return (0);
}

t_line_lst	*fil_list(char *line)
{
	t_line_lst	*head;
	note_type	last_type;
	int			i;
	int			len;

	i = 0;
	head = NULL;
	line = ft_strtrim(line, " ");
	while (line[i])
	{
		last_type = get_last_type(head);
		if (is_word(line[i]))	// command, word or filename. Use the previous type to check the grammer
		{
			len = 0;
			while (is_word(line[i + len]))
				len++;
			if (last_type == e_start || last_type == e_pipe)
				add_at_end_of_list(&head, e_cmd, ft_substr(line, i, len));
			if (last_type == e_cmd || last_type == e_word)
				add_at_end_of_list(&head, e_word, ft_substr(line, i, len));
			if (last_type == e_redirect_i || last_type == e_redirect_o || last_type == e_delimiter || last_type == e_append)
				add_at_end_of_list(&head, e_file, ft_substr(line, i, len));
			i += len - 1;
		}
		if (line[i] == '|')
			add_at_end_of_list(&head, e_pipe, "|");
		if (line[i] == '<')
		{
			i++; 
			if (line[i] != '<')
			{
				add_at_end_of_list(&head, e_redirect_i, "<");
				continue;
			}
			add_at_end_of_list(&head, e_delimiter, "<<");
		}	
		if (line[i] == '>')
		{
			i++;
			if (line[i] != '>')
			{
				add_at_end_of_list(&head, e_redirect_o, ">");
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

t_line_lst	*parser(char *line)
{
	t_line_lst	*head;

	head = fil_list(line);
	return (head);
}
