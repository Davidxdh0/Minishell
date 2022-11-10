/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 15:47:26 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/10 16:03:21 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

/* echo with option -n
	iets met -nnnnnnn
*/

int	check_option(char **cmd)
{
	int i;
	int j;
	int flag;
	
	flag = 0;
	i = 0;
	while (cmd[i])
	{
		j = 2;
		while ((cmd[i][0] == '-' && cmd[i][1] == 'n') && cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return(0);
}

void	execute_echo(char **cmd)
{
	int option;
	
	option = 0;
	if (cmd[1])
		if (cmd[1][0] == '-' && cmd[1][1] == 'n')
			option = check_option(cmd);
	while (option != 0 && cmd[option])
	{
		printf("%s", cmd[option]);
		if (cmd[option + 1] != NULL)
			printf(" ");
		option++;
	}
}