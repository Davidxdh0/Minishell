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

bool	ft_env(t_envp *envp, int fd)
{
	int	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp)
	{
		if (envp->value)
		{
			write(fd, envp->line, ft_strlen(envp->line));
			write(fd, "\n", 1);
		}
		envp = envp->next;
	}
	return (true);
}
