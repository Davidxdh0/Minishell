/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:22 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:24 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_pwd(int fd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_perror("getcwd: ", 1, NULL);
		return ;
	}
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
}
