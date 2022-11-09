/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 15:47:26 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/09 18:10:46 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

/* echo with option -n
	iets met -nnnnnnn
*/

int	check_option(char **cmd)
{
	int i;
	int flag;
	
	flag = 0;
	i = 0;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n')
	{
		while ((cmd[1][i] == '-' && cmd[1][i + 1] && cmd[1][i + 1] == 'n') || (cmd[1][i] == 'n'))
		{
			flag = i;
			if (cmd[1][i] == 'n' || cmd[1][i] == '-')
				i++;
			while(cmd[1][i] == ' ')
				i++;
			if (flag != i)
				i++;
			if (cmd[1][i+1] == '\0')
				break ;
		}
	}
	return(i);
}
void	execute_echo(char **cmd)
{
	int i;
	int option;
	
	option = check_option(cmd);
	i = option;
	//cmd[1] += option;

	// printf("%s", cmd[1]);
	//message(*cmd);
}