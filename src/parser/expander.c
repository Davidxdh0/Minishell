/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 17:59:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/14 13:27:48 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_line_lst	*expander(t_line_lst *line_lst)
{
	t_line_lst *temp;
	char *tempstring;
	
	temp = line_lst;
	while (line_lst != NULL)
	{
		tempstring = ft_strdup(line_lst->value);
		if (line_lst->type == e_whitespace && line_lst->state == 0)
		{
			// printf("next");
			line_lst->prev->next = line_lst->next;
		}
		while (line_lst->next != NULL && line_lst->next->state > 0)
		{
			line_lst = line_lst->next;
			tempstring = ft_strjoin(tempstring, line_lst->value);
		}
		line_lst = line_lst->next;
	}
	// printf("string = %s\n", tempstring);
	return (temp);
}

// t_execute *alloc_execute_list(t_line_lst *head)
// {
// 	int i;
// 	int k;
// 	t_execute *cmdlist = NULL;
//  	t_execute *last = NULL;
	
// 	while (head != NULL)
// 	{
// 		i = count_commands(head);
// 		k = 0;
// 		t_execute *new_node = malloc(sizeof(t_execute));
//         new_node->cmd = malloc(sizeof(char *) * (i + 1));
//         new_node->next = NULL;
// 		while (head != NULL && k < i)
// 		{
//             new_node->cmd[k] = ft_strdup(head->value);
//             // printf("new_node->cmd[%d] == %s\n", k, new_node->cmd[k]);
//             head = head->next;
//             k++;
// 		}
// 		new_node->cmd[k] = NULL;
// 		if (last == NULL)
//             cmdlist = new_node;
//         else
//             last->next = new_node;
// 		last = new_node;
// 		if (head != NULL && !ft_strncmp(head->value,"|", 1))
// 			;// printf("value head == %s\n", head->value);
// 		if (head != NULL)
// 			head = head->next;
// 	}
// 	return (cmdlist);
// }