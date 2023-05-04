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

bool	ft_getenv_int(int *env, const char *name, char **envp)
{
	int	i;
	int	j;

	i = 0;
	if (!name | !envp)
		return (false);
	while (envp[i])
	{
		j = 0;
		while (name[j] == envp[i][j])
		{
			j++;
			if (!name[j])
			{
				*env = i;
				return (true);
			}
		}
		i++;
	}
	*env = -1;
	return (false);
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
