/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:33:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/15 20:08:35 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	copy_cmd_rdr(t_execute *d_node, char **cmd_list, int rd)
{
	int	i;
	int	j;
	int	cmd_index;

	i = 0;
	j = 0;
	cmd_index = 0;
	while (cmd_list[i])
	{
		if (!ft_strcmp(cmd_list[i], ">") || !ft_strcmp(cmd_list[i], ">>") || \
		!ft_strcmp(cmd_list[i], "<") || !ft_strcmp(cmd_list[i], "<<"))
		{
			d_node->redirects[j] = ft_strdup(cmd_list[i]);
			j++;
			i++;
			d_node->redirects[j] = ft_strdup(cmd_list[i]);
			j++;
			rd--;
		}
		else
			d_node->cmd[cmd_index++] = ft_strdup(cmd_list[i]);
		i++;
	}
	d_node->cmd[cmd_index] = NULL;
	d_node->redirects[j] = NULL;
}

t_execute	*create_new_node(int num_commands, int num_redirects)
{
	t_execute	*new_node;

	new_node = ft_malloc(sizeof(t_execute));
	new_node->cmd = ft_malloc(sizeof(char *) * (num_commands + 1));
	new_node->redirects = ft_malloc(sizeof(char *) * (num_redirects * 2 + 1));
	new_node->next = NULL;
	return (new_node);
}

int	count_redirects(char **cmd_list)
{
	int	num_redirects;
	int	i;

	num_redirects = 0;
	i = 0;
	while (cmd_list[i])
	{
		if (!ft_strcmp(cmd_list[i], ">") || !ft_strcmp(cmd_list[i], ">>") || \
		!ft_strcmp(cmd_list[i], "<") || !ft_strcmp(cmd_list[i], "<<"))
			num_redirects++;
		i++;
	}
	return (num_redirects);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
