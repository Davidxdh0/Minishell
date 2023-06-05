/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:11 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/05 21:50:13 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp for show_t_list function 

char	*type_to_string(node_type type)
{
	static char	*type_strings[13];

	type_strings[e_start] = "start\t";
	type_strings[e_cmd] = "cmd\t";
	type_strings[e_file] = "file\t";
	type_strings[e_pipe] = "pipe\t";
	type_strings[e_word] = "word\t";
	type_strings[e_quote] = "quote\t";
	type_strings[e_dquote] = "dquote\t";
	type_strings[e_whitespace] = "wspace\t";
	type_strings[e_var] = "var\t";
	type_strings[e_redirect_i] = "redirect_i";
	type_strings[e_redirect_o] = "redirect_o";
	type_strings[e_delimiter] = "delimiter";
	type_strings[e_append] = "append\t";
	if (type >= e_start && type <= e_append)
		return (type_strings[type]);
	return ("Not in my list");
}

void	delete_t_exec(t_execute *cmd)
{
	t_execute	*cur_node;
	t_execute	*next_node;	
	int			i;

	cur_node = cmd;
	while (cur_node != NULL)
	{
		next_node = cur_node->next;
		i = 0;
		while (cur_node->cmd != NULL && cur_node->cmd[i] != NULL)
		{
			free(cur_node->cmd[i]);
			i++;
		}
		free(cur_node->cmd);
		i = 0;
		while (cur_node->redirects != NULL && cur_node->redirects[i] != NULL)
		{
			free(cur_node->redirects[i]);
			i++;
		}
		free(cur_node->redirects);
		free(cur_node);
		cur_node = next_node;
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
