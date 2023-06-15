/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   daycare.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 16:43:11 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/15 17:33:21 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	first_child(int *pipe, t_execute *cmd_struct, t_envp *envp)
{
	close(pipe[0]);
	redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name);
	if (!redirect_outfile(cmd_struct->redirects))
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			exit(ft_perror(NULL, 1, NULL));
	}
	close(pipe[1]);
	ft_execute_cmd(cmd_struct, envp);
}

void	middle_child(int *pipe_in, int *pipe_out, t_execute *cmd_struct
																, t_envp *envp)
{
	close(pipe_in[1]);
	if (!redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name))
	{	
		if (dup2(pipe_in[0], STDIN_FILENO) == -1)
			exit(ft_perror(NULL, 1, NULL));
	}
	close(pipe_in[0]);
	close(pipe_out[0]);
	if (!redirect_outfile(cmd_struct->redirects))
	{
		if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
			exit(ft_perror(NULL, 1, NULL));
	}
	close(pipe_out[1]);
	ft_execute_cmd(cmd_struct, envp);
}

void	last_child(int *pipe, t_execute *cmd_struct, t_envp *envp)
{
	close(pipe[1]);
	if (!redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name))
	{	
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			exit(ft_perror(NULL, 1, NULL));
	}
	close(pipe[0]);
	redirect_outfile(cmd_struct->redirects);
	ft_execute_cmd(cmd_struct, envp);
}

t_execute	*middle_child_loop(t_execute *cmd_struct, t_envp *envp
											, int **pipes, int *pid)
{
	int	i;

	i = 1;
	cmd_struct = cmd_struct->next;
	while (i + 1 < cmd_struct->count_cmd)
	{
		pipes[i] = ft_malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			exit(ft_perror(NULL, 1, cmd_struct));
		pid[i] = fork();
		if (pid[i] == -1)
			exit(ft_perror(NULL, 1, cmd_struct));
		if (pid[i] == 0)
			middle_child(pipes[i - 1], pipes[i], cmd_struct, envp);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		i++;
		cmd_struct = cmd_struct->next;
	}
	return (cmd_struct);
}

void	child_cleanup(t_execute *cmd_struct, int **pipes, int *pid, int i)
{
	int	status;

	if (close(pipes[i - 1][0]) == -1)
		exit(ft_perror(NULL, 1, cmd_struct));
	if (close(pipes[i - 1][1]) == -1)
		exit(ft_perror(NULL, 1, cmd_struct));
	i = 0;
	while (i < cmd_struct->count_cmd)
	{
		waitpid(pid[i], &status, 0);
		g_exitcode = WEXITSTATUS(status);
		exitcode_signals(status);
		i++;
	}
	free(pid);
	i = 0;
	while (i + 1 < cmd_struct->count_cmd)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
