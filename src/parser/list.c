/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:26:11 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/28 22:19:51 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>	// temp for show_t_list function 

char	*type_to_string(node_type type)
{
    static char* type_strings[13];
	
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
        return type_strings[type];
    return "Not in my list";
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
		node = node->next;
		i++;
	}
	printf("-------- end line list table ---------\n\n");
}


void	delete_t_list(t_line_lst *head)
{
	t_line_lst	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

void delete_t_exec(t_execute *cmd)
{
    t_execute *current_node = cmd;
    t_execute *next_node;

    while (current_node != NULL)
    {
        next_node = current_node->next;
        int i = 0;
        while (current_node->cmd != NULL && current_node->cmd[i] != NULL)
        {
            free(current_node->cmd[i]);
            i++;
        }
        free(current_node->cmd);

        i = 0;
        while (current_node->redirects != NULL && current_node->redirects[i] != NULL)
        {
            free(current_node->redirects[i]);
            i++;
        }
        free(current_node->redirects);
        free(current_node);
        current_node = next_node;
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
