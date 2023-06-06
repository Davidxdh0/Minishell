/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:04 by abarteld      #+#    #+#                 */
/*   Updated: 2023/06/06 15:20:16 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static int	validate_exit_arg(char *str)
{
	long	arg;
	int		i;

	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	if (long_atoi(str, &arg) == false)
		return (-1);
	arg %= 256;
	return ((int)arg);
}

void	ft_exit(t_execute *cmd_struct)
{
	int	i;
	int	arg;

	i = 0;
	if (!cmd_struct->next && !cmd_struct->prev)
		ft_putstr_fd("exit\n", 1);
	if (!cmd_struct->cmd[1])
		exit(g_exitcode);
	arg = validate_exit_arg(cmd_struct->cmd[1]);
	if (arg == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd_struct->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (cmd_struct->cmd[2])
	{
		g_exitcode = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	exit(arg);
}

		/*
	check number of arguments (if too many, dont exit, error 1)
	check argument validity (if invalid, exit, error 255)
	set exit status to arg[1]
	if !arg[1], exit status == exit status of last executed command
	write (2, exit\n) or is it 1??
	exit [exit status]
		*/
