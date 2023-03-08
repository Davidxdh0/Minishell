/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list_len.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 09:03:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/08 09:03:54 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	list_len(t_stack *stack)
{
	int	len;

	len = 0;
	while (stack)
	{
		len++;
		stack = stack->next;
	}
	return (len);
}
