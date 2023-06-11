/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: david <david@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 15:21:41 by david         #+#    #+#                 */
/*   Updated: 2023/03/08 09:00:14 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_isspace(int c)
// {
// 	return (c == '\t' || c == '\n' || c == '\v'
// 		|| c == '\f' || c == '\r' || c == ' ');
// }

int	ft_atoi(const char *str)
{
	int			i;
	int			minorplus;
	int			number;

	number = 0;
	i = 0;
	minorplus = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minorplus *= -1;
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	while (ft_isdigit(str[i]))
	{
		number *= 10;
		number += (str[i] - '0');
		i++;
	}
	return (number * minorplus);
}
