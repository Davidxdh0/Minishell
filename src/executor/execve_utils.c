/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execve_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 11:08:10 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/20 13:10:49 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

bool	is_path(char *exec_argv)
{
	if (!ft_strcmp(exec_argv, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		exit(2);
	}
	if (!ft_strcmp(exec_argv, ".."))
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		exit(127);
	}
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

	if (!envp)
		return (NULL);
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
	access_path = find_command(path, base_path);
	if (access(access_path, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exec_argv, 2);
		ft_putstr_fd(": command not found\n", 2);
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
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		exit(127);
	}
	if (is_path(exec_argv))
	{
		if (access(exec_argv, F_OK))
			exit(ft_perror(exec_argv, 127, NULL));
		return (ft_strdup(exec_argv));
	}
	env_hold = ft_getenv("PATH=", envp);
	if (env_hold)
	{
		path = ft_split(env_hold, ':');
		return (get_path(exec_argv, path));
	}
	else
		return (ft_strdup(exec_argv));
}
