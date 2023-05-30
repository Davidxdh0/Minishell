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
	char	*buf; // wd name capped (at 1024) by a certain rule, source needed

	buf = getcwd(NULL, 0);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	free(buf);
}
