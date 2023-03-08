/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list_add_back.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 08:55:58 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/08 08:58:51 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	listadd_back(t_stack **stack, t_stack *current)
{
	t_stack	*last;

	last = list_last(*stack);
	if (last != NULL)
	{
		last->next = current;
		current->previous = last;
	}
	else
		*stack = current;
}
