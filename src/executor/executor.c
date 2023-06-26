/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_dcs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 15:04:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/22 19:20:45 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_heredoc_cleanup(t_execute *cmd_struct)
{
	while (cmd_struct)
	{
		if (cmd_struct->heredoc_name)
		{
			unlink(cmd_struct->heredoc_name);
			free(cmd_struct->heredoc_name);
			cmd_struct->heredoc_name = NULL;
		}
		cmd_struct = cmd_struct->next;
	}
}

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
	return (true);
}

t_envp	*executor_dcs(t_execute *cmd_struct, t_envp *envp)
{
	if (!count_cmd_structs(cmd_struct))
		return (envp);
	sig_controller(2);
	if (ft_heredoc_init(cmd_struct, envp))
	{
		enable_ctrl_c_display();
		if (cmd_struct->count_cmd > 1)
			ft_multiple_commands(cmd_struct, envp);
		else
			envp = ft_single_command(cmd_struct, envp);
	}
	else
		g_exitcode = 1;
	ft_heredoc_cleanup(cmd_struct);
	return (envp);
}
