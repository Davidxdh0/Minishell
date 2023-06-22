/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:23:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/22 19:12:03 by dyeboa        ########   odam.nl         */
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

// export david="  dav        id"
// echo $david "$david"
char	*expand_spaces(char *str)
{
	size_t	i;
	char	*newstr;
	int		j;

	j = 0;
	i = ft_strlen(str);
	newstr = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			newstr[j] = str[i];
			while (str[i] && str[i] == ' ')
				i++;
			i--;
		}
		else
			newstr[j] = str[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
