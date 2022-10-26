/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 16:48:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 16:49:18 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_line_in_history(char **line)
{
	if (*line && **line)
		add_history (*line);
}
