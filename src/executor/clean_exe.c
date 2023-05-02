#include "../main/main.h"

void	connect_pipe_out(t_execute *cmd_struct, int pipe_out[2])
{
	if (pipe(pipe_out) == -1)
		ft_exit_error("Some Pipes Fucked Up, Pipe_Out", errno);
	close(pipe_out[0]);
	if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
		ft_exit_error("Some Pipe Fucked Up, Pipe_Out", errno);
exit(printf("\nMagical Debugging Tool #3\n"));
	close(pipe_out[1]);
}

void	connect_pipe_in(t_execute *cmd_struct, int pipe_in[2])
{
	close(pipe_in[1]);
	if (dup2(pipe_in[0], STDIN_FILENO) == -1)
		ft_exit_error("Some Pipe Fucked Up, Pipe In", errno);
	close(pipe_in[0]);
}

void	ft_execute_command
(t_execute *cmd_struct, char **envp, int pipe_new[2], int pipe_old[2])
{
// exit(printf("\nMagical Debugging Tool NUMBER 2\n"));
	if (cmd_struct->next)
		connect_pipe_out(cmd_struct, pipe_new);
exit(printf("\nMagical Debugging Tool\n"));
	if (cmd_struct->prev)
		connect_pipe_in(cmd_struct, pipe_old);
	redirect_infile(cmd_struct->redirects);
	redirect_outfile(cmd_struct->redirects);
	ft_execute_cmd(cmd_struct, envp);
	// if (cmd_struct->prev)
	// {
	// 	close(pipe_old[0]);
	// 	close(pipe_old[1]);
	// }
	// if (cmd_struct->next)
	// {
	// 	pipe_old[0] = pipe_new[0];
	// 	pipe_old[1] = pipe_new[1];
	// }

}

void	ft_execute_command_struct(t_execute *cmd_struct, char **envp)
{
	int	pipe1[2];
	int	pipe2[2];
	// int	*pid;

	// pid = malloc(sizeof(int) * cmd_struct->count_cmd);
	// if (!pid)
	// 	ft_exit_error("Malloc Failed", 2);
	while (cmd_struct)
	{
		ft_execute_command(cmd_struct, envp, pipe1, pipe2);
		cmd_struct = cmd_struct->next;
	}
	// waitpid()
	// free(pid);
}
// printf("\nMagical Debugging Tool\n");
