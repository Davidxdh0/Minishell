/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/07/11 20:51:57 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		g_exitcode;

int	ft_isredirect(char *str)
{
	if (ft_strcmp(str, ">") || ft_strcmp(str, ">>") || ft_strcmp(str, "<") \
	|| ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

void	show(t_execute *cmd)
{
	int	i;

	printf("\n");
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->cmd != NULL && cmd->cmd[i] != NULL)
		{
			printf("cmd[%d] = %s\n", i, cmd->cmd[i]);
			i++;
		}
		i = 0;
		if (cmd->redirects != NULL && cmd->redirects[0] != NULL)
		{
			while (cmd->redirects != NULL && cmd->redirects[i] != NULL)
			{
				printf("redir = %s\n", cmd->redirects[i]);
				i++;
			}
		}
		cmd = cmd->next;
		printf("\n");
	}
}

// show_t_list(line_lst, line);
// show(cmd);

t_envp	*shell(char *line, t_envp *envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;
	t_line_lst	*filler;

	filler = NULL;
	line_lst = parser(line);
	if (syntax_count_quotes(line_lst))
		return (envp);
	line_lst = variable_expand(line_lst, envp);
	line_lst = combine_quotes(line_lst);
	line_lst = remove_quotes(line_lst, filler, filler);
	line_lst = combine_values(line_lst, line_lst, filler);
	line_lst = rm_wspace(line_lst, filler, filler, filler);
	if (!syntax_check(line_lst))
	{
		cmd = alloc_execute_list(line_lst, NULL, NULL);
		envp = executor_dcs(cmd, envp);
		delete_t_exec(cmd);
	}
	else
		g_exitcode = 258;
	if (line_lst != NULL)
		delete_t_list(line_lst);
	return (envp);
}

// void	leakschk(void)
// {
// 	system("leaks -q minishell"); //remove
// }

// enable_ctrl_c_display();
// system("leaks -q minishell");
// atexit(leakschk);
int	main(int argc, char *argv[], char **original_envp)
{
	char		*line;
	t_envp		*envp;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Minishell Does Not Take Arguments\n", 2), 1);
	envp = copy_envp(original_envp);
	g_exitcode = 0;
	while (1)
	{
		disable_ctrl_c_display();
		sig_controller(0);
		sig_controller(3);
		line_reader(&line, "minishell$ ");
		if (line != NULL)
		{
			envp = shell(line, envp);
			free(line);
		}
	}
	return (0);
}
