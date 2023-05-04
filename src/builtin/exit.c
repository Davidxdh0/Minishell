/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:04 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:06 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	ft_exit(t_execute *cmd_struct, char **envp) // add an fd?
{
	// write(1, "Exit\n", 5);
	// if (cmd_struct->next || cmd_struct->prev)
	// 	return (EXIT_FAILURE); // it doesnt work when piped, still needs to throw errors first
	// if (!cmd_struct->cmd[1])
	// {
	// 	// free(shit that needs freeing);
	// 	// return (exit status)
	// }
	// else if (cmd_struct->cmd[2])
	// {
	// 	// error: too many argument
	// }
	// // check if arg 1 is 
}
