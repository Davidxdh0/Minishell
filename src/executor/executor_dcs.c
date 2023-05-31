/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_dcs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 15:04:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/31 11:22:13 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

bool	redirect_infile(char **list, char *name)
{
	int		i;
	bool	file;
	int		fd;

	file = false;
	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '<' && list[i][1] != '<')
		{
			i++;
			if (dup2(open(list[i], O_RDONLY), STDIN_FILENO) == -1)
				ft_exit_error("Couldn't Redirect Infile", errno); //errors and stuff
			file = true;
		}
		if (list[i][0] == '<' && list[i][1] == '<')
		{
			i++;
			fd = open(name, O_RDONLY);
			if (dup2(fd, STDIN_FILENO) == -1)
				ft_exit_error("Couldn't Redirect HereDoc To Infile", errno); //errors and stuff
			file = true;
		}
		i++;
	}
	// printf("No Redirect To Infile Found\n");
	return (file); //close fds
}

bool	redirect_outfile(char **list)
{
	int		i;
	bool	file;

	file = false;
	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '>' && !list[i][1])
		{
			i++;
			if (dup2(open(list[i], O_WRONLY | O_TRUNC | O_CREAT, 0644) \
			, STDOUT_FILENO) == -1)
				ft_exit_error("Couldn't Redirect Outfile", errno); //errors and stuff
			// return (true);
			file = true;
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			if (dup2(open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644) \
			, STDOUT_FILENO) == -1)
				ft_exit_error("Dup2? More Like \'Dumb Too\'\n", errno); //errors and stuff
			// return (true);
			file = true;
		}
		i++;
	}
	// printf("No Redirect To Outfile Found\n");
	return (file); //close fds
}

static void	first_child(int *pipe, t_execute *cmd_struct, t_envp *envp)
{
	close(pipe[0]);
	redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name);
	if (!redirect_outfile(cmd_struct->redirects))
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, First Child", errno);
	}
	close(pipe[1]);
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("First Child Survived", 13);
}

static void	middle_child
(int *pipe_in, int *pipe_out, t_execute *cmd_struct, t_envp *envp)
{
	close(pipe_in[1]);
	if (!redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name))
	{	
		if (dup2(pipe_in[0], STDIN_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, Middle Child - In", errno);
	}
	close(pipe_in[0]);
	close(pipe_out[0]);
	if (!redirect_outfile(cmd_struct->redirects))
	{
		if (dup2(pipe_out[1], STDOUT_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, Middle Child - Out", errno);
	}
	close(pipe_out[1]);
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("Middle Child Survived", 17);
}

static void	last_child(int *pipe, t_execute *cmd_struct, t_envp *envp)
{
	close(pipe[1]);
	if (!redirect_infile(cmd_struct->redirects, cmd_struct->heredoc_name))
	{	
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, Last Child", errno);
	}
	close(pipe[0]);
	redirect_outfile(cmd_struct->redirects);
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("Last Child Survived", 19);
}

void	ft_execute_cmd(t_execute *cmd_struct, t_envp *envp)
{
	char	*cmd_path;
	char	**envp_array;
	
	if (!cmd_struct->cmd)
		exit(g_exitcode);
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
		ft_exit_error("Execve Failed", 13); // change for proper errors etc
	}
}

void	ft_multiple_commands(t_execute *cmd_struct, t_envp *envp) // 2 pipe logic?
{
	int		**pipes;
	int		*pid;
	int		i;

	pipes = malloc(sizeof(int *) * (cmd_struct->count_cmd - 1));
	pid = malloc(sizeof(int) * cmd_struct->count_cmd);
	if (!pipes || !pid)
		ft_exit_error("Malloc Failed", 2);
	i = 0;
	pipes[i] = malloc(sizeof(int) * 2);
	if (!pipes[i])
		ft_exit_error("Malloc Failed", 2);
	if (pipe(pipes[i]) == -1)
		ft_exit_error("Some Pipes Fucked Up, Parent", errno);
	pid[i] = fork();
	// if (pid[i] == -1) //looped checks?
	// 	exit (errno);
	if (pid[i] == 0)
		first_child(pipes[i], cmd_struct, envp);
	i++;
	cmd_struct = cmd_struct->next;
	while (i + 1 < cmd_struct->count_cmd)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			ft_exit_error("Malloc Failed", 2);
		if (pipe(pipes[i]) == -1)
			ft_exit_error("Some Pipes Fucked Up, Parent - Loop", errno);
		pid[i] = fork();
		if (pid[i] == 0)
			middle_child(pipes[i - 1], pipes[i], cmd_struct, envp);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		i++;
		cmd_struct = cmd_struct->next;
	}
	pid[i] = fork();
	// if (pid[i] == -1) //looped checks?
	// 	exit (errno);
	if (pid[i] == 0)
		last_child(pipes[i - 1], cmd_struct, envp);
	if (close(pipes[i - 1][0]) == -1)
		ft_exit_error("Closing The Pipe Went Wrong", errno);
	if (close(pipes[i - 1][1]) == -1)
		ft_exit_error("Closing The Pipe Went Wrong", errno);
	i = 0;
	while (i < cmd_struct->count_cmd)
		waitpid(pid[i++], NULL, 0);
	free(pid);
	i = 0;
	while (i + 1 < cmd_struct->count_cmd)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	executor_dcs(t_execute *cmd_struct, t_envp *envp) // MAKE A PROTECTED MALLOC
{
// system("leaks -q minishell");
printf("\n\tStarted Executing\n");
	t_execute	*next;
	next = cmd_struct->next;
	cmd_struct->count_cmd = 1;
	while (next)
	{
		next = next->next;
		cmd_struct->count_cmd++;
	}
	next = cmd_struct;
	int	i = 1;
	while (next)
	{
		next->count_cmd = cmd_struct->count_cmd;
		i++;
		next = next->next;
	}
printf("Number Of Commands = #%d\n", cmd_struct->count_cmd);
	ft_heredoc_init(cmd_struct);
	if (cmd_struct->count_cmd > 1)
		ft_multiple_commands(cmd_struct, envp);
	else
		ft_single_command(cmd_struct, envp);
	ft_heredoc_cleanup(cmd_struct);
	free(next);
printf("\tFinished Executing\n\n");
// system("leaks -q minishell");
}


	/* 

	copy the envp, in order to add/remove stuff


if (commands > 1)
{
	fork for each command
	do everything as is
}
if (commands == 1)
{
	fork only if not a builtin
	if (fork)
		normal shit
	else
	{
		open AND close infiles (but dont dup2)
		open and close outfiles (saving the open fd of the last one)
		call the builtin, using the fd saved.
	}
}
	*/

// 1, regular failure
// 127, file permissions?
// 130, signals?
// 131, signals?
// 255, exit shit??
// 258 bad 