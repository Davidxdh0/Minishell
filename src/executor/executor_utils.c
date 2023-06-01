/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 11:03:27 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 11:03:31 by abarteld      ########   odam.nl         */
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
			if (dup2(open(list[i], O_RDONLY), STDIN_FILENO) == -1) //split open and dup
				ft_exit_error("Couldn't Redirect Infile", errno); //errors and stuff
			file = true;
		}
		if (list[i][0] == '<' && list[i][1] == '<')
		{
			i++;
			fd = open(name, O_RDONLY); // error check open
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
			, STDOUT_FILENO) == -1) //split open and dup
				ft_exit_error("Couldn't Redirect Outfile", errno); //errors and stuff
			file = true;
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			if (dup2(open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644) \
			, STDOUT_FILENO) == -1) //split open and dup
				ft_exit_error("Dup2? More Like \'Dumb Too\'\n", errno); //errors and stuff
			file = true;
		}
		i++;
	}
// printf("No Redirect To Outfile Found\n");
	return (file); //close fds
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	ptr = malloc(size);
	if (!ptr)
		ft_exit_error("Malloc Failed", errno);
	return (ptr);
}

int	ft_perror(char *str, int error_number)
{
	g_exitcode = error_number;
// printf("errno = %d\n", errno);
	perror(str);
	return (error_number);
}

int	ft_exit_error(char *str, int err)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(err);
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

// bool	ft_getenv_int(int *env, const char *name, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!name | !envp)
// 		return (false);
// 	while (envp[i])
// 	{
// 		j = 0;
// 		while (name[j] == envp[i][j])
// 		{
// 			j++;
// 			if (!name[j])
// 			{
// 				*env = i;
// 				return (true);
// 			}
// 		}
// 		i++;
// 	}
// 	*env = -1;
// 	return (false);
// }

char	*find_command(char **path, char *basepath)
{
	int		i;
	char	*access_path;

	i = 0;
	access_path = NULL;
	while (!access_path)
	{
		access_path = ft_strjoin(path[i], basepath);
		if (path[i + 1] && access(access_path, F_OK))
		{
			free(access_path);
			access_path = NULL;
			i++;
		}
	}
	printf("Access Path = %s\n", access_path);
	return (access_path);
}

char	*get_path(char *exec_argv, char **path)
{
	char	*base_path;
	char	*access_path;

	access_path = NULL;
	base_path = ft_strjoin("/", exec_argv);
	access_path = find_command(path, base_path);
	if (access(access_path, F_OK))
	{
		write(2, "minishell: ", 11);
		write(2, exec_argv, ft_strlen(exec_argv));
		write(2, ": command not found\n", 20);
		exit(127);
	}
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
		return (get_path(exec_argv, path));
	}
	else
		return (ft_strdup(exec_argv));
}
