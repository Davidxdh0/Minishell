/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:39:53 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 17:50:32 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	Get chars and $variables between quotes.
*/
char	*get_data_in_quotes(char *str)
{
	ft_putendl_fd("", 1);
	ft_putchar_fd(*(str), 1);
	ft_putendl_fd("", 1);
	return (str);
}
