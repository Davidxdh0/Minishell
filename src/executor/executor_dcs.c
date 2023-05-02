/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 15:04:30 by abarteld      #+#    #+#                 */
/*   Updated: 2023/03/19 15:04:34 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	ft_exit_error(char *str, int err)
{
	// printf("Error\n%s\n", str);
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (err);
}

bool	malloc_perror(void *str, char **arr)
{
	if (!(str || arr))
	{
		perror("Malloc Failed");
		return (true);
	}
	return (false);
}

char	**free_char_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

bool	is_path(char *exec_argv)
{
	if (exec_argv[0] == '/')
		return (true);
	if (exec_argv[0] == '.' && exec_argv[1] == '/')
		return (true);
	if (exec_argv[0] == '.' && exec_argv[1] == '.' && \
	exec_argv[2] == '/')
		return (true);
	return (false);
}

char	*ft_getenv(const char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (name[j] == envp[i][j])
		{
			j++;
			if (!name[j])
				return (envp[i] + j);
		}
		i++;
	}
	return (NULL);
}

char	*find_command(char **path, char *basepath)
{
	int		i;
	char	*access_path;

	i = 0;
	access_path = NULL;
	while (!access_path)
	{
		access_path = ft_strjoin(path[i], basepath);
		if (malloc_perror(access_path, NULL))
			exit(errno);
		if (path[i + 1] && access(access_path, F_OK))
		{
			free(access_path);
			access_path = NULL;
			i++;
		}
	}
	return (access_path);
}

char	*get_path(char *exec_argv, char **path)
{
	char	*base_path;
	char	*access_path;

	access_path = NULL;
	base_path = ft_strjoin("/", exec_argv);
	if (malloc_perror(base_path, NULL))
		exit(errno);
	access_path = find_command(path, base_path);
	free_char_array(path);
	free(base_path);
	return (access_path);
}

char	*check_path(char *exec_argv, char **envp)
{
	char	**path;
	char	*env_hold;

	if (!exec_argv)
		return (NULL);
	if (!exec_argv[0])
		return ("");
	if (is_path(exec_argv))
		return (ft_strdup(exec_argv));
	env_hold = ft_getenv("PATH=", envp);
	if (env_hold)
	{
		path = ft_split(env_hold, ':');
		if (malloc_perror(NULL, path))
			exit(errno);
		return (get_path(exec_argv, path));
	}
	else
		return (ft_strdup(exec_argv));
}

// int	open_infile(t_execute *cmd_struct)
// {

// }

bool	redirect_infile(char **list)
{
	int		i;
	bool	file;

	file = false;
	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '<')
		{
			i++;
			if (dup2(open(list[i], O_RDONLY), STDIN_FILENO) == -1)
				ft_exit_error("Couldn't Redirect Infile", errno); //errors and stuff
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

static void	first_child(int *pipe, t_execute *cmd_struct, char **envp)
{
	char	*cmd_path;

	close(pipe[0]);
	redirect_infile(cmd_struct->redirects);
	if (!redirect_outfile(cmd_struct->redirects))
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, First Child", errno);
	}
	close(pipe[1]);
	// cmd_path = check_path(cmd_struct->cmd[0], envp);
	// if (check_builtin(cmd_struct->cmd[0]))
	// {
	// 	printf("EXEC Builtin, First\n");
	// 	exec_builtin(cmd_struct, envp);
	// }
	// else
	// {
	// 	cmd_path = check_path(cmd_struct->cmd[0], envp);
	// 	execve(cmd_path, cmd_struct->cmd, envp);
	// }
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("First Child Survived", 13);
}

static void	middle_child
(int *pipe_in, int *pipe_out, t_execute *cmd_struct, char **envp)
{
// printf("Middle Command = %s\n", cmd_struct->cmd[0]);
	char	*cmd_path;

	close(pipe_in[1]);
	if (!redirect_infile(cmd_struct->redirects))
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
	// cmd_path = check_path(cmd_struct->cmd[0], envp);
	// // printf("\n Command Path = %s\n", cmd_path);
	// if (check_builtin(cmd_struct->cmd[0]))
	// {
	// 	printf("EXEC Builtin, Middle\n");
	// 	exec_builtin(cmd_struct, envp);
	// }
	// else
	// {
	// 	cmd_path = check_path(cmd_struct->cmd[0], envp);
	// 	execve(cmd_path, cmd_struct->cmd, envp);
	// }
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("Middle Child Survived", 17);
}

static void	last_child(int *pipe, t_execute *cmd_struct, char **envp)
{
	char	*cmd_path;

	close(pipe[1]);
	if (!redirect_infile(cmd_struct->redirects))
	{	
		if (dup2(pipe[0], STDIN_FILENO) == -1)
			ft_exit_error("Some Pipe Fucked Up, Last Child", errno);
	}
	close(pipe[0]);
	redirect_outfile(cmd_struct->redirects);
	// if (dup2(open("./outfile", O_WRONLY | O_TRUNC | O_CREAT, 0644) \
	// , STDOUT_FILENO) == -1)
	// 	exit(errno);
	// printf("\nCommand Path = %s\n", cmd_path);
	// if (check_builtin(cmd_struct->cmd[0]))
	// {
	// 	printf("EXEC Builtin, Last\n");
	// 	exec_builtin(cmd_struct, envp);
	// }
	// else
	// {
	// 	cmd_path = check_path(cmd_struct->cmd[0], envp);
	// 	execve(cmd_path, cmd_struct->cmd, envp);
	// }
	ft_execute_cmd(cmd_struct, envp);
	ft_exit_error("Last Child Survived", 19);
}

void	ft_execute_cmd(t_execute *cmd_struct, char **envp)
{
	char	*cmd_path;

	// cmd_path = check_path(cmd_struct->cmd[0], envp);
	if (check_builtin(cmd_struct->cmd[0]))
	{
		printf("EXEC Builtin, Start\n");
		exec_builtin(cmd_struct, envp);
	}
	else
	{
		// add pid + fork + waitpid
		cmd_path = check_path(cmd_struct->cmd[0], envp);
		execve(cmd_path, cmd_struct->cmd, envp);
		ft_exit_error("Execve Failed", 13);
	}
}

void	ft_single_command(t_execute *cmd_struct, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_exit_error("Fork Failed", 177);
	if (pid == 0)
	{
		redirect_infile(cmd_struct->redirects);
		redirect_outfile(cmd_struct->redirects);
		ft_execute_cmd(cmd_struct, envp);
	}
	waitpid(pid, NULL, 0);
	ft_env(envp, 1);
}

void	ft_multiple_commands(t_execute *cmd_struct, char **envp)
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

void	executor_dcs(t_execute *cmd_struct, char **envp)
{
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
	while (next)
	{
		next->count_cmd = cmd_struct->count_cmd;
		next = next->next;
	}

	// cmd_struct->std_in = dup(STDIN_FILENO);
	// cmd_struct->std_out = dup(STDOUT_FILENO);
	// if (cmd_struct->std_fds[0] == -1 || cmd_struct->std_fds[1] == -1)
	// 	ft_exit_error("Couldn't Duplicate Standard In/Out\n", 25);

// printf("Number Of Commands = #%d\n", cmd_struct->count_cmd);
	if (cmd_struct->count_cmd > 1)
		ft_multiple_commands(cmd_struct, envp);
	else
		ft_single_command(cmd_struct, envp);


	// ft_execute_command_struct(cmd_struct, envp);

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