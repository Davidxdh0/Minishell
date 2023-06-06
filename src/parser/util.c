/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:23:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/06 14:51:27 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	perror_return(char *msg2)
{
	char	*msg;

	msg = ft_strdup("minishell: syntax error near unexpected token ");
	write(2, msg, ft_strlen(msg));
	if (msg)
		write(2, msg2, ft_strlen(msg2));
	write(2, "\n", 1);
	return (1);
}
