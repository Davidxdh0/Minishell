/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:34:54 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:34:56 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

bool	ft_env(char **envp, int fd)
{
	int	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (true);
}
