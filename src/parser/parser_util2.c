/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util_extra.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:35:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/28 21:38:12 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

char **make_redirects(t_line_lst *line_lst)
{
	char **tempstring;
	t_line_lst *temp;
	int i;

	tempstring = NULL;
	i = 0;
	temp = line_lst;
	while (temp != NULL && ft_strcmp(line_lst->value, "|"))
	{
		if (ft_isredirect(line_lst->value))
			i++;
		else if (ft_isredirect(line_lst->prev->value))
			i++;
		temp = temp->next;
	}
	tempstring = malloc(sizeof(char **) * i + 1);
	temp = line_lst;
	i = 0;
	while (line_lst != NULL && ft_strncmp(line_lst->value, "|", 1))
	{
		if (ft_isredirect(line_lst->value))
			tempstring[i] = ft_strdup(line_lst->value);
		else if (ft_isredirect(line_lst->prev->value))
			tempstring[i] = ft_strdup(line_lst->value);
		i++;
		temp = temp->next;
	}
	// printf("string = %s\n", tempstring);
	return (tempstring);
}

t_execute *alloc_execute_list(t_line_lst *head)
{
    int k;
    t_execute *cmdlist = NULL;
    t_execute *last = NULL;
    char *temp;
    while (head != NULL)
    {
        k = 0;
        t_execute *new_node = malloc(sizeof(t_execute));
        new_node->count_cmd = count_commands(head);
        new_node->cmd = malloc(sizeof(char *) * (new_node->count_cmd + 1));
		new_node->redirects = NULL;
        new_node->next = NULL;
        while (head != NULL && k < new_node->count_cmd)
        {
            if (head->state > 0)
            {
                temp = make_string(head);
                if (temp[0] == '\"' || temp[0] == '\'')
                    new_node->cmd[k] = ft_substr(temp, 1, ft_strlen(temp) - 2);
                while (head != NULL && head->state > 0)
                    head = head->next;
				free(temp);
				temp = NULL;
            }
            else
            {
                new_node->cmd[k] = ft_strdup(head->value);
                head = head->next;
            }
            k++;
        }
        new_node->cmd[k] = NULL;
        if (last == NULL)
            cmdlist = new_node;
        else
            last->next = new_node;
        last = new_node;
        if (head != NULL && !ft_strncmp(head->value, "|", 1))
            ;
        if (head != NULL)
            head = head->next;
    }
    // printf("cmdlist = %s", cmdlist->cmd[0]);
    return (cmdlist);
}

char *make_string(t_line_lst *line_lst)
{
	char *tempstring;

	tempstring = NULL;
	if (line_lst->value)
		tempstring = ft_strdup(line_lst->value);
	while (line_lst != NULL && ft_strncmp(line_lst->value, "|", 1))
	{
		while (line_lst->next != NULL && line_lst->next->state > 0)
		{
			line_lst = line_lst->next;
			tempstring = ft_strjoin(tempstring, line_lst->value);
		}
		line_lst = line_lst->next;
	}
	// printf("string = %s\n", tempstring);
	return (tempstring);
}