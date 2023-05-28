#include "../main/main.h"

void	ft_single_command(t_execute *cmd_struct, char **envp)
{
	int	pid;
	int	fd;

	// if (!command_exists(cmd_struct))
	// 	(no_command_redirects(cmd_struct->redirects))
	if (check_builtin(cmd_struct->cmd[0]))
	{
		
		builtin_infile(cmd_struct->redirects);
		fd = 1;
		if (!builtin_outfile(cmd_struct->redirects, &fd))
			; //write error message for shit failing
		else
			exec_builtin(cmd_struct, envp, fd);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			ft_exit_error("Fork Failed", 177);
		else if (pid == 0)
		{
			redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name);
			redirect_outfile(cmd_struct->redirects);
			ft_execute_cmd(cmd_struct, envp);
		}
		else
			waitpid(pid, NULL, 0);
	}
	// ft_env(envp, 1);
}


// void	ft_execute_command
// (t_execute *cmd_struct, char **envp, int pipe_new[2], int pipe_old[2])
// {
// // exit(printf("\nMagical Debugging Tool NUMBER 2\n"));
// 	if (cmd_struct->next)
// 		connect_pipe_out(cmd_struct, pipe_new);
// exit(printf("\nMagical Debugging Tool\n"));
// 	if (cmd_struct->prev)
// 		connect_pipe_in(cmd_struct, pipe_old);
// 	redirect_infile(cmd_struct->redirects);
// 	redirect_outfile(cmd_struct->redirects);
// 	ft_execute_cmd(cmd_struct, envp);
// 	// if (cmd_struct->prev)
// 	// {
// 	// 	close(pipe_old[0]);
// 	// 	close(pipe_old[1]);
// 	// }
// 	// if (cmd_struct->next)
// 	// {
// 	// 	pipe_old[0] = pipe_new[0];
// 	// 	pipe_old[1] = pipe_new[1];
// 	// }

// }

// void	ft_execute_command_struct(t_execute *cmd_struct, char **envp)
// {
// 	int	pipe1[2];
// 	int	pipe2[2];
// 	// int	*pid;

// 	// pid = malloc(sizeof(int) * cmd_struct->count_cmd);
// 	// if (!pid)
// 	// 	ft_exit_error("Malloc Failed", 2);
// 	while (cmd_struct)
// 	{
// 		ft_execute_command(cmd_struct, envp, pipe1, pipe2);
// 		cmd_struct = cmd_struct->next;
// 	}
// 	// waitpid()
// 	// free(pid);
// }
// // printf("\nMagical Debugging Tool\n");
