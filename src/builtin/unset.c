/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:35:36 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:35:40 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

t_envp	*ft_unset(t_execute *cmd_struct, t_envp *envp)
{
// ft_env(envp, 1);
	t_envp	*ptr;
	int		i;

	i = 1;
// show_envp_struct(envp);
	while (cmd_struct->cmd[i])
	{
		// Validate Args
		ptr = envp;
		while (ptr)
		{
			if (!ft_strcmp(cmd_struct->cmd[i], ptr->identifier))
			{
// show_envp_node(ptr);
				envp = remove_envp_node(ptr);
// show_envp_node(envp);
				break ;
			}
			ptr = ptr->next;
		}
		i++;
	}
	return (envp);
// ft_env(envp, 1);
}
/*
	argument:
	string
	check for forbidden characters
	strjoin string + '='
	if string = variable
		delete variable

	next argument
*/

	// if (!cmd_struct->cmd[1])
	// 	ft_exit_error("Unset Error Message", 20);
		// name = ft_strjoin(cmd_struct->cmd[i], "=");
		// if (!name)
		// 	ft_exit_error("Malloc Failed", 2);
		// // if (ft_getenv_int(&env, name, envp))
		// // {
		// // 	while (envp[env])
		// // 	{
		// // 		envp[env] = envp[env + 1];
		// // 		env++;
		// // 	}
		// // }
		// free(name);
		// i++;