/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_util.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:43:50 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/05 14:27:54 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

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

void	show_t_list(t_line_lst *node, char *input_line)
{
	int	i;

	i = 1;
	printf("\ninput__line = %s", input_line);
	printf("\n-----------line list table ------------\n");
	printf("index \ttype \tlen \ttype_name \tstate\tvalue\n");
	while (node != NULL)
	{
		printf("%d\t%d\t%d\t%s\t%d\t%s\n", i, node->type, node->len,
			type_to_string(node->type), (int)node->state, node->value);
		node = node->next;
		i++;
	}
	printf("-------- end line list table ---------\n\n");
}
