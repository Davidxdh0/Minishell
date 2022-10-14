/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:26:18 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/05/27 17:53:56 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*pdes;
	unsigned char	*psrc;
	size_t			i;

	pdes = (unsigned char *)s1;
	psrc = (unsigned char *)s2;
	i = 0;
	while (n > 0)
	{
		*pdes = *psrc;
		if (*psrc == (unsigned char)c)
			return (pdes + 1);
		pdes++;
		psrc++;
		n--;
	}
	return (NULL);
}
