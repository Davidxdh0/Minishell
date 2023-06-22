/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 11:03:27 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/22 19:55:19 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(ft_perror(NULL, errno, NULL));
	return (ptr);
}

int	ft_perror(char *str, int error_number, t_execute *cmd_struct)
{
	g_exitcode = error_number;
	ft_putstr_fd("minishell: ", 2);
	if (str && !str[0])
		ft_putstr_fd(": ", 2);
	perror(str);
	if (cmd_struct)
		ft_heredoc_cleanup(cmd_struct);
	return (error_number);
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

char	*ft_str_fuse(char *s1, char *s2)
{
	char	*str;
	int		loop;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_malloc(len1 + len2 + 1);
	loop = 0;
	while (loop < len1)
	{
		str[loop] = s1[loop];
		loop++;
	}
	while (loop < len1 + len2)
	{
		str[loop] = s2[loop - len1];
		loop++;
	}
	str[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (str);
}

void	exitcode_signals(int status)
{
	int	exit_status;

	if (WIFSIGNALED(status) == true)
	{
		exit_status = WTERMSIG(status);
		if (exit_status == 2)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			g_exitcode = 130;
		}
		else if (exit_status == 3)
		{
			ft_putstr_fd("Quit: 3", 2);
			ft_putstr_fd("\n", 2);
			g_exitcode = 131;
		}
	}
}
