/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list_last.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 08:56:31 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/08 08:58:44 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*list_last(t_stack *stack)
{
	while (stack)
	{
		if (stack->next == NULL)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}
