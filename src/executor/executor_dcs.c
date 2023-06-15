/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_dcs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 15:04:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/15 17:14:53 by dyeboa        ########   odam.nl         */
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
	return (true);
}

t_envp	*executor_dcs(t_execute *cmd_struct, t_envp *envp)
{
	if (!count_cmd_structs(cmd_struct))
		return (envp);
	sig_controller(1);
	if (ft_heredoc_init(cmd_struct, envp))
	{
		sig_controller(2);
		sig_controller(3);
		enable_ctrl_c_display();
		if (cmd_struct->count_cmd > 1)
			ft_multiple_commands(cmd_struct, envp);
		else
			envp = ft_single_command(cmd_struct, envp);
	}
	else
		g_exitcode = 1;
	ft_heredoc_cleanup(cmd_struct);
// system("leaks -q minishell");
	return (envp);
}

// void	exitcode_signals(int status)
// {
// 	int	exit_status;

// 	if (WIFSIGNALED(status) == true)
// 	{
// 		exit_status = WTERMSIG(status);
// 		if (exit_status == 2)
// 			g_exitcode = 130;
// 		else if (exit_status == 3)
// 		{
// 			g_exitcode = 131;
// 			ft_putstr_fd("Quit: 3", 2);
// 		}
// 		ft_putstr_fd("\n", 2);
// 	}
// }
