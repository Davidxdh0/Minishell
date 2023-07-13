/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 11:23:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/04 15:48:55 by dyeboa        ########   odam.nl         */
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

char	*perror_red(t_line_lst *line)
{
	if (line->next == NULL)
		return (line->value);
	if (ft_strcmp(line->next->value, "|") && ft_strcmp(line->value, ">>"))
		return ("|");
	else
		return (line->value);
}

int	perror_redirect(t_line_lst *line)
{
	char	*msg;

	msg = perror_red(line);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (ft_strcmp(msg, ">") || ft_strcmp(msg, ">>"))
		ft_putstr_fd(msg, 2);
	else if ((ft_strcmp(msg, "<") || ft_strcmp(msg, "<<")))
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
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
	newstr = ft_malloc(sizeof(char) * (i + 1));
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
