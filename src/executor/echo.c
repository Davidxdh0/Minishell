/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 15:47:26 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/09 17:01:41 by dyeboa        ########   odam.nl         */
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
	if (cmd[1][0] == "-" && cmd[1][1] == "n")
	{
		i = 0;
		while (cmd[1][i] == "-" || cmd[1][i] == "n" | cmd[1][i] == " ")
		{
			if (cmd[1][i] != "n" && cmd[1][i] != " ")
				return(i);
			if (cmd[1][i] == " ")
				i++;
			if (cmd[1][i] == "n" && (cmd[1][i-1] != "-"))
				return(i);
			
		}
	}
}
void	execute_echo(t_line_lst *stack, char **cmd)
{
	int i;

	i = 0;
	
	while(cmd[i])
	{
		write
	}
}