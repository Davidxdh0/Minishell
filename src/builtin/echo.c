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

static bool	echo_option(char *str)
{
	int	i;

	if (str[0] != '-' && str[1] != 'n')
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

void	ft_echo(t_execute *cmd_struct, int fd)
{
	int		i;
	bool	n;

	i = 1;
	if (cmd_struct->cmd[i])
		n = echo_option(cmd_struct->cmd[i]);
	else
		n = false;
	if (n)
		i++;
	if (cmd_struct->cmd[i])
	{
		write(fd, cmd_struct->cmd[i], ft_strlen(cmd_struct->cmd[i]));
		i++;
	}
	while (cmd_struct->cmd[i])
	{
		write(fd, " ", 1);
		write(fd, cmd_struct->cmd[i], ft_strlen(cmd_struct->cmd[i]));
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}
