/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/02 16:19:18 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/28 18:33:55 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static bool		echo_option(char *str)
{
	int	i;

	if (str[0] != '-' && str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] == ' ') // might be a problem, test "-nnn XX"
			break ;
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return(true);
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
	while (cmd_struct->cmd[i])
	{
		write(fd, cmd_struct->cmd[i], ft_strlen(cmd_struct->cmd[i]));
		i++;
	}
	if (!n)
		write(fd, "\n", 1);
}

void	ft_pwd(int fd)
{
	char	buf[10000];  // working directory name is capped (at 1024) by a certain rule, source needed

	getcwd(buf, 10000);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
}