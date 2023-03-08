/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 08:56:55 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/08 08:58:41 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*list_new(int i)
{
	t_stack	*list_new;

	list_new = malloc(sizeof(t_stack));
	if (!list_new)
		return (NULL);
	list_new->i = i;
	list_new->previous = NULL;
	list_new->next = NULL;
	return (list_new);
}
