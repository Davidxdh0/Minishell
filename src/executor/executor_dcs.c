/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_dcs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 15:04:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/28 19:26:14 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	count_cmd_structs(t_execute *cmd_struct)
{
	t_execute	*head;
	int			count;
	
	if (!cmd_struct)
		return (false);
	head = cmd_struct;
	count = 0;
	while (cmd_struct)
	{
		cmd_struct = cmd_struct->next;
		count++;
	}
	cmd_struct = head;
	while (cmd_struct)
	{
		cmd_struct->count_cmd = count;
		cmd_struct = cmd_struct->next;
	}
printf("Number Of Commands = #%d\n", head->count_cmd);
	return (true);
}

t_envp	*executor_dcs(t_execute *cmd_struct, t_envp *envp) // MAKE A PROTECTED MALLOC
{
system("leaks -q minishell");
printf("\n\tStarted Executing\n");

	if (!count_cmd_structs(cmd_struct))
		return (envp);
	ft_heredoc_init(cmd_struct);
	if (cmd_struct->count_cmd > 1)
		ft_multiple_commands(cmd_struct, envp);
	else
		envp = ft_single_command(cmd_struct, envp);
	ft_heredoc_cleanup(cmd_struct);
printf("\tFinished Executing\n\n");
	return (envp);
system("leaks -q minishell");
}

// 1, regular failure
// 127, command not found
// 130, signals?
// 131, signals?
// 255, exit shit??
// 258 syntax error