/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 11:36:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/28 11:36:39 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../main/main.h"

/* check testers voor alle builtins.
cd
echo
pwd
export
%?
exit
unset
*/
void	execute_builtins(t_line_lst *cmdlist, t_data *data)
{
	
	if (!cmdlist)
		return ;
	if (cmdlist->type == 0)
		execute_cd(cmdlist);
	if (cmdlist->type == 1)
		execute_echo(cmdlist);
	if (cmdlist->type == 2)
		execute_pwd(cmdlist);
	if (cmdlist->type == 3)
		execute_export(cmdlist);
	if (cmdlist->type == 4)
		execute_exit_code(cmdlist);
	if (cmdlist->type == 4)
		execute_unset(cmdlist, data);
		
}
