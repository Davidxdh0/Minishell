/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtoupper.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 09:58:52 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/09/29 21:12:38 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

/*
// gcc -Wall -Werror -Wextra ft_strtoupper.c ft_toupper.c ft_islower.c 
// ft_strdup.c ft_strlen.c && ./a.out && rm a.out

#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strdup("AaBbCc");
	str = ft_strtoupper(str);
	printf("%s\n", str);
	free(str);
	return (0);
}
*/
