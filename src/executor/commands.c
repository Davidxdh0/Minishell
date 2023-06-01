#include "../main/main.h"

void	ft_execute_cmd(t_execute *cmd_struct, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_array;
	
	if (cmd_struct->cmd == NULL)
		exit(g_exitcode);
printf("cmd_struct pointer = %p\n", cmd_struct->cmd);
	if (check_builtin(cmd_struct->cmd[0]))
	{
printf("EXEC Builtin, Start\n");
		exec_builtin(cmd_struct, envp, 1);
	}
	else
	{
		envp_array = envp_to_array(envp);
		cmd_path = check_path(cmd_struct->cmd[0], envp_array);
		execve(cmd_path, cmd_struct->cmd, envp_array);
		exit(ft_perror("Execve Failed", errno));
	}
}

t_envp	*ft_single_command(t_execute *cmd_struct, t_envp *envp)
{
	int	pid;
	int	fd;
	int	status;

	if (cmd_struct->cmd && check_builtin(cmd_struct->cmd[0]))
	{
		ft_heredoc_cleanup(cmd_struct);
		builtin_infile(cmd_struct->redirects);
		fd = 1;
		if (!builtin_outfile(cmd_struct->redirects, &fd))
			; //write error message for shit failing
		else
			envp = exec_builtin(cmd_struct, envp, fd);
	}
	else
	{
printf("Single Execve Entry\tg_exitcode = %d\n", g_exitcode);
		pid = fork();
		if (pid == -1)
			exit(ft_perror(NULL, errno));
		if (pid == 0)
		{
			redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name);
			redirect_outfile(cmd_struct->redirects);
			ft_execute_cmd(cmd_struct, envp);
		}
		waitpid(pid, &status, 0);
		g_exitcode = WEXITSTATUS(status);
printf("Single Execve Exit\tg_exitcode = %d\n", g_exitcode);
	}
	return (envp);
}

void	ft_multiple_commands(t_execute *cmd_struct, t_envp *envp)
{
	int		**pipes;
	int		*pid;
	int		i;

	pipes = ft_malloc(sizeof(int *) * (cmd_struct->count_cmd - 1));
	pid = ft_malloc(sizeof(int) * cmd_struct->count_cmd);
	i = 0;
	pipes[i] = ft_malloc(sizeof(int) * 2);
	if (pipe(pipes[i]) == -1)
		exit(ft_perror(NULL, errno));
	pid[i] = fork();
	if (pid[i] == -1)
		exit(ft_perror(NULL, errno));
	if (pid[i] == 0)
		first_child(pipes[i], cmd_struct, envp);
	i++;
	cmd_struct = middle_child_loop(cmd_struct, envp, pipes, pid, &i);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(ft_perror(NULL, errno));
	if (pid[i] == 0)
		last_child(pipes[i - 1], cmd_struct, envp);
	child_cleanup(cmd_struct, pipes, pid, i);
}


	// if (!command_exists(cmd_struct))
	// 	(no_command_redirects(cmd_struct->redirects))
	// exit(printf("DEATH\n"));
	// if (!cmd_struct->cmd)
	// {
	// 	builtin_infile(cmd_struct->redirects);
	// 	builtin_outfile(cmd_struct->redirects, &fd);
	// }
