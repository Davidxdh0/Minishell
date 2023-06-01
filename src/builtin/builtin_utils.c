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
#include <limits.h>

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
	if (atoi > (unsigned long long)__LONG_LONG_MAX__ + 1 ||
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

void	builtin_infile(char **list)
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
				ft_exit_error("Couldn't Open Builtin Infile", errno); //errors and stuff
			if (close(fd) == -1)
				ft_exit_error("Couldn't Close Builtin Infile", errno); //errors and stuff
		}
		i++;
	}
printf("Looped Through Builtin Infiles\n");
}

bool	builtin_outfile(char **list, int *fd)
{
	int		i;
	int		temp_fd;
	bool	file;

	file = false;
	i = 0;
	temp_fd = -1;
	while (list && list[i])
	{
		if (list[i][0] == '>' && !list[i][1])
		{
			i++;
			if (temp_fd != -1 && close(temp_fd) == -1)
				ft_exit_error("Couldn't Close Builtin Outfile", errno); //errors and stuff
			temp_fd = open(list[i], O_WRONLY | O_TRUNC | O_CREAT, 0644); // does this need its own error check?
			if (temp_fd == -1)
				ft_exit_error("Couldn't Open Builtin Outfile", errno); //errors and stuff
			file = true;
		}
		else if (list[i][0] == '>' && list[i][1] == '>')
		{
			i++;
			if (temp_fd != -1 && close(temp_fd) == -1)
				ft_exit_error("Couldn't Close Builtin Outfile", errno); //errors and stuff
			temp_fd = open(list[i], O_WRONLY | O_APPEND | O_CREAT, 0644); // does this need its own error check?
			if (temp_fd == -1)
				ft_exit_error("Couldn't Open Builtin Outfile", errno); //errors and stuff
			file = true;
		}
		i++;
	}
	if (file == true)
	{
printf("fd Set\n");
		*(fd) = temp_fd;
	}
	else
	{
printf("fd = 1\n");
		*(fd) = 1;
	}
printf("Looped Through Builtin Outfiles\n");
	return (true);
}

// no file >>> fd = 1
// correct file >>> fd = open(file)
// erronous file >>> do not execute builtin
