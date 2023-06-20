/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals_util.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/11 16:50:29 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/15 13:55:39 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	disable_ctrl_c_display(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

//voor shell en na wifexit
void	enable_ctrl_c_display(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*combine_thestring(char *first, char *second)
{
	int		len;
	int		len2;
	char	*str;

	len = ft_strlen(first);
	len2 = ft_strlen(second);
	str = ft_malloc(sizeof(char *) * len + 1 + len2 + 1 + 1);
	ft_strlcpy(str, first, len + len2 + 1);
	ft_strlcat(str, second, len + len2 +1);
	free(first);
	return (str);
}
