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
	printf("Error\n%s\n", str);
	exit (err);
}

/*
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


static void	child1(int *p, char **argv, char **envp)
{
	char	**exec_argv;
	char	*access_path;

	close(p[0]);
	if (dup2(open(argv[1], O_RDONLY), STDIN_FILENO) == -1)
		exit(errno);
	if (dup2(p[1], STDOUT_FILENO) == -1)
		exit(errno);
	close(p[1]);
	exec_argv = ft_split(argv[2], ' ');
	if (malloc_perror(NULL, exec_argv))
		exit(errno);
	access_path = check_path(exec_argv[0], envp);
	execve(access_path, exec_argv, envp);
	exit(127);
}

static void	child2(int *p, char **argv, char **envp)
{
	char	**exec_argv;
	char	*access_path;

	if (!argv[4][0])
	{
		printf("Error: Cannot Create File With Empty Name\n");
		exit(258);
	}
	close(p[1]);
	if (dup2(p[0], STDIN_FILENO) == -1)
		exit(errno);
	if (dup2(open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644) \
	, STDOUT_FILENO) == -1)
		exit(errno);
	close(p[0]);
	exec_argv = ft_split(argv[3], ' ');
	if (malloc_perror(NULL, exec_argv))
		exit(errno);
	access_path = check_path(exec_argv[0], envp);
	execve(access_path, exec_argv, envp);
	exit(127);
}

static int	ft_pipex(char **argv, char **envp)
{
	int		p[2]; // use clear variable names
	int		pid[2];
	int		exit_code;
	int		status;

	if (pipe(p) == -1)
		exit(errno);
	pid[0] = fork();
	if (pid[0] == -1)
		exit (errno);
	if (pid[0] == 0)
		child1(p, argv, envp);
	pid[1] = fork();
	if (pid[1] == -1)
		exit (errno);
	if (pid[1] == 0)
		child2(p, argv, envp);
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &status, 0); // only wait for last command
	waitpid(pid[1], &status, 0);
	exit_code = WEXITSTATUS(status);
	return (exit_code);
}
*/

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

static bool	redirect_infile(char **list)
{
	int	i;

	i = 0;
	if (list[i][0] == '<') //change for redirects
	{
		i++;
		if (dup2(open(list[i], O_RDONLY), STDIN_FILENO) == -1)
			exit(errno);
		return (true);
	}
	printf("No Redirect To Infile Found\n");
	return (false);
}

static bool	redirect_outfile(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i][0] == '>' && !list[i][1])
		{
			i++;
			if (dup2(open(list[i], O_WRONLY | O_TRUNC | O_CREAT, 0644) \
			, STDOUT_FILENO) == -1)
				exit(errno);
			return (true); //change for redirects
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			if (dup2(open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644) \
			, STDOUT_FILENO) == -1)
				ft_exit_error("Dup2? More Like \'Dumb Too\'\n", errno); //change
			return (true); //change for redirects
		}
		i++;
	}
	printf("No Redirect To Outfile Found\n");
	return (false);
}

static void	first_child(int *pipes, t_execute *cmd_struct)
{
	char	*cmd_path;

	close(pipes[0]);
	redirect_infile(cmd_struct->cmd);
	if (!redirect_outfile(cmd_struct->cmd))
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			ft_exit_error("Some Pipes Fucked Up, First Child", errno);
	}
	close(pipes[1]);
	// cmd_struct->cmd[0] = ft_strdup("cat");
	// cmd_struct->cmd[1] = ft_strdup("out");
	// cmd_struct->cmd[3] = NULL;
	cmd_path = check_path(cmd_struct->cmd[0], g_data.envp);
	execve(cmd_path, cmd_struct->cmd, g_data.envp);
	ft_exit_error("Execve Failed", 13);
}

static void	middle_child(int *pipes_in, int *pipes_out, t_execute *cmd_struct)
{
	char	*cmd_path;

	if (!redirect_infile(cmd_struct->cmd))
	{	
		if (dup2(pipes_in[0], STDIN_FILENO) == -1)
			ft_exit_error("Some Pipes Fucked Up, Middle Child - In", errno);
	}
	close(pipes_in[0]);
	if (!redirect_outfile(cmd_struct->cmd))
	{
		if (dup2(pipes_out[1], STDOUT_FILENO) == -1)
			ft_exit_error("Some Pipes Fucked Up, Middle Child - Out", errno);
	}
	close(pipes_out[1]);
	cmd_struct->cmd[3] = NULL;
	cmd_path = check_path(cmd_struct->cmd[0], g_data.envp);
	execve(cmd_path, cmd_struct->cmd, g_data.envp);
	ft_exit_error("Execve Failed", 17);
}

static void	last_child(int *pipes, t_execute *cmd_struct)
{
	char	*cmd_path;

	close(pipes[1]);
	if (dup2(pipes[0], STDIN_FILENO) == -1)
		ft_exit_error("Some Pipes Fucked Up, Last Child", errno);
	// if (dup2(open(cmd_struct->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644) \
	// , STDOUT_FILENO) == -1)
		// exit(errno);
	close(pipes[0]);
	cmd_path = check_path(cmd_struct->cmd[0], g_data.envp);
	execve(cmd_path, cmd_struct->cmd, g_data.envp);
	ft_exit_error("Execve Failed", 19);
}

void	ft_needsname(t_execute *cmd_struct)
{
	// char	*cmd_path;
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
		first_child(pipes[i], cmd_struct);
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
		{
printf("Middle Command = %s\n", cmd_struct->cmd[0]);
			middle_child(pipes[i - 1], pipes[i], cmd_struct);
		}
		i++;
		cmd_struct = cmd_struct->next;
	}
printf("#i after middle loop = %d\n", i);
	pid[i] = fork();
	// if (pid[i] == -1) //looped checks?
	// 	exit (errno);
	if (pid[i] == 0)
		last_child(pipes[i - 1], cmd_struct);
	i = 0;
	while (i + 1 < cmd_struct->count_cmd)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	// cmd_path = check_path(cmd_struct->cmd[0], g_data.envp);
	// if (!cmd_path)
	// 	ft_exit_error("Could Not Find The Path", 11);
	// execve(cmd_path, cmd_struct->cmd, g_data.envp);
	// ft_exit_error("Execve Failed", 11);
}


void	executor_dcs(t_execute *cmd_struct)
{
printf("\nStart Executing\n");

ft_pwd(1);
int	i = 0;
	cmd_struct->cmd[i++] = ft_strdup("echo");
	cmd_struct->cmd[i++] = ft_strdup("-nnnnnnnnnnnnnnnn");
	cmd_struct->cmd[i++] = ft_strdup("TESTING ECHO\n");
	cmd_struct->cmd[i++] = ft_strdup("TESTING ECHO\n");
	cmd_struct->cmd[i++] = NULL;
ft_echo(cmd_struct, 1);
exit(117);

	t_execute *next;
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
printf("Number Of Commands = #%d\n", cmd_struct->count_cmd);
	ft_needsname(cmd_struct);

printf("Finished Executing\n\n");
}

// Read after filename
// Read white space
// Read Empty String
