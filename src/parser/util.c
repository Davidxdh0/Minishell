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

int	perror_return(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
