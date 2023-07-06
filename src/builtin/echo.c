/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:34:34 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/01 19:50:29 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool	echo_option_check(char *str)
{
	int	i;

	if ((str[0] != '-' || str[1] != 'n'))
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	echo_option(char **arr, bool *n)
{
	int		i;
	bool	option;

	option = true;
	i = 1;
	while (arr[i] && option == true)
	{
		option = echo_option_check(arr[i]);
		if (option == true)
		{
			i++;
			*n = true;
		}
	}
	return (i);
}

void	ft_echo(t_execute *cmd_struct, int fd)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (cmd_struct->cmd[1])
		i = echo_option(cmd_struct->cmd, &n);
	if (cmd_struct->cmd[i])
	{
		ft_putstr_fd(cmd_struct->cmd[i], fd);
		i++;
		while (cmd_struct->cmd[i])
		{
			write(fd, " ", 1);
			ft_putstr_fd(cmd_struct->cmd[i], fd);
			i++;
		}
	}
	if (n == false)
		write(fd, "\n", 1);
}
