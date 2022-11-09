/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 11:36:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/09 14:50:46 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* check testers voor alle builtins.
cd
echo
pwd
export
$?
exit
unset
*/

int		is_builtin(char *str)
{
	int i;

	i = 0;
	if (!ft_strncmp(str, "cd", 2))
		i = 1;
	if (!ft_strncmp(str, "echo", 4))
		i = 1;
	if (!ft_strncmp(str, "pwd", 3))
		i = 1;
	if (!ft_strncmp(str, "export", 5))
		i = 1;
	if (!ft_strncmp(str, "$?", 2))
		i = 1;;
	if (!ft_strncmp(str, "unset", 5))
		i = 1;
	return (i);
}
void	execute_builtin(t_line_lst *cmdlist, char **cmd)
{
	if (!cmdlist)
		return ;
	if (!ft_strncmp(cmdlist->value, "cd", 2))
	{
		execute_cd(cmdlist, cmd);
	}
	// if (!ft_strcmp(cmdlist->value, "echo"))
	// 	execute_echo(cmdlist);
	// if (!ft_strcmp(cmdlist->value, "pwd"))
	// 	execute_pwd(cmdlist);
	// if (!ft_strcmp(cmdlist->value, "export"))
	// 	execute_export(cmdlist);
	// if (!ft_strcmp(cmdlist->value, "$?"))
	// 	execute_exit_code(cmdlist);
	// if (!ft_strcmp(cmdlist->value, "unset"))
	// 	execute_unset(cmdlist, data);
}
