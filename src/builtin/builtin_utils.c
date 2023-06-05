/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:36:17 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:36:20 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_envp	*ft_export_cmd(char *cmd, char *target, t_envp *envp)
{
	t_envp	*head;

	head = envp;
	if (!target)
	{
		while (envp)
		{
			if (!ft_strcmp(cmd, envp->identifier))
				return (head);
			envp = envp->next;
		}
	}
	else if (export_targeted(cmd, target, envp))
		return (envp);
	envp = head;
	if (!envp)
		envp = envp_start_list(cmd);
	else
		envp_add_node(envp, cmd);
	return (envp);
}

static unsigned long long	string_to_ull(const char *str, bool neg)
{
	unsigned long long	atoi;

	atoi = 0;
	while (*str >= '0' && *str <= '9')
	{
		atoi *= 10;
		atoi += *str - 48;
		str++;
		if ((atoi > __LONG_LONG_MAX__) && (neg == false))
			return ((unsigned long long)__LONG_LONG_MAX__ + 2);
		if ((atoi > (unsigned long long)__LONG_LONG_MAX__ + 1) && (neg == true))
			return ((unsigned long long)__LONG_LONG_MAX__ + 3);
	}
	return (atoi);
}

bool	long_atoi(const char *str, long *number)
{
	unsigned long long	atoi;
	bool				neg;

	neg = false;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = true;
		str++;
	}
	atoi = string_to_ull(str, neg);
	if (atoi > (unsigned long long)__LONG_LONG_MAX__ + 1 || \
		(atoi > __LONG_LONG_MAX__ && neg == 0))
		return (false);
	if (atoi == (unsigned long long)__LONG_LONG_MAX__ + 1)
		*number = (__LONG_LONG_MAX__ * -1) - 1;
	else
	{
		*number = (long)atoi;
		if (neg == true)
			atoi *= -1;
	}
	return (true);
}

bool	builtin_infile(char **list)
{
	int	i;
	int	fd;

	i = 0;
	while (list && list[i])
	{
		if (list[i][0] == '<' && list[i][1] != '<')
		{
			i++;
			fd = open(list[i], O_RDONLY);
			if (fd == -1)
				return (ft_perror(list[i], 1), false);
			if (close(fd) == -1)
				return (ft_perror(NULL, 1), false);
		}
		i++;
	}
	return (true);
}

bool	builtin_outfile(char **list, int *fd, int i, int temp_fd)
{
	while (list && list[i])
	{
		if (list[i][0] == '>' && !list[i][1])
		{
			i++;
			if (temp_fd != -1 && close(temp_fd) == -1)
				return (ft_perror(NULL, 1), false);
			temp_fd = open(list[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (temp_fd == -1)
				return (ft_perror(list[i], 1), false);
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			if (temp_fd != -1 && close(temp_fd) == -1)
				return (ft_perror(NULL, 1), false);
			temp_fd = open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (temp_fd == -1)
				return (ft_perror(list[i], 1), false);
		}
		i++;
	}
	if (temp_fd != -1)
		*(fd) = temp_fd;
	return (true);
}
