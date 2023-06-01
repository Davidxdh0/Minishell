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

void	ft_env(t_envp *envp, int fd)
{
	while (envp)
	{
		if (envp->value)
		{
			write(fd, envp->line, ft_strlen(envp->line));
			write(fd, "\n", 1);
		}
		envp = envp->next;
	}
}

// show_envp_struct(envp);
// return (true);