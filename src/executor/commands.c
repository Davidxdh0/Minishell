/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/04 16:07:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/06 15:22:09 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_execute_cmd(t_execute *cmd_struct, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_array;

	if (cmd_struct->cmd == NULL)
		exit(g_exitcode);
	if (check_builtin(cmd_struct->cmd[0]))
		exec_builtin(cmd_struct, envp, 1);
	else
	{
		envp_array = envp_to_array(envp);
		cmd_path = check_path(cmd_struct->cmd[0], envp_array);
		execve(cmd_path, cmd_struct->cmd, envp_array);
		exit(ft_perror(cmd_path, 1));
	}
}

static void	only_child(t_execute *cmd_struct, t_envp *envp)
{
	redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name);
	redirect_outfile(cmd_struct->redirects);
	ft_execute_cmd(cmd_struct, envp);
}

t_envp	*ft_single_command(t_execute *cmd_struct, t_envp *envp)
{
	int	pid;
	int	fd;
	int	status;

	if (cmd_struct->cmd && check_builtin(cmd_struct->cmd[0]))
	{
		ft_heredoc_cleanup(cmd_struct);
		fd = 1;
		if (builtin_infile(cmd_struct->redirects) && \
			builtin_outfile(cmd_struct->redirects, &fd, 0, -1))
			envp = exec_builtin(cmd_struct, envp, fd);
		return (envp);
	}
	pid = fork();
	if (pid == -1)
		exit(ft_perror(NULL, 1));
	if (pid == 0)
		only_child(cmd_struct, envp);
	waitpid(pid, &status, 0);
	g_exitcode = WEXITSTATUS(status);
	return (envp);
}

void	ft_multiple_commands(t_execute *cmd_struct, t_envp *envp)
{
	int		**pipes;
	int		*pid;
	int		i;

	pipes = ft_malloc(sizeof(int *) * (cmd_struct->count_cmd - 1));
	pid = ft_malloc(sizeof(int) * cmd_struct->count_cmd);
	pipes[0] = ft_malloc(sizeof(int) * 2);
	if (pipe(pipes[0]) == -1)
		exit(ft_perror(NULL, 1));
	pid[0] = fork();
	if (pid[0] == -1)
		exit(ft_perror(NULL, 1));
	if (pid[0] == 0)
		first_child(pipes[0], cmd_struct, envp);
	cmd_struct = middle_child_loop(cmd_struct, envp, pipes, pid);
	i = cmd_struct->count_cmd - 1;
	pid[i] = fork();
	if (pid[i] == -1)
		exit(ft_perror(NULL, 1));
	if (pid[i] == 0)
		last_child(pipes[i - 1], cmd_struct, envp);
	child_cleanup(cmd_struct, pipes, pid, i);
}
