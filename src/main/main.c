/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:51 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/08 16:07:57 by dyeboa        ########   odam.nl         */
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
int	shell(char *line, t_envp *envp)
{
	t_line_lst	*line_lst;
	t_execute	*cmd;

	line_lst = parser(line);
	if (syntax_count_quotes(line_lst))
		return (0);
	line_lst = variable_expand(line_lst, envp);
	line_lst = combine_quotes(line_lst);
	line_lst = remove_quotes(line_lst);
	line_lst = combine_values(line_lst);
	line_lst = remove_whitespace_list(line_lst);
	if (!syntax_check(line_lst))
	{
		cmd = alloc_execute_list(line_lst);
		cmd = acco(cmd);
		executor_dcs(cmd, envp);
		delete_t_exec(cmd);
	}
	else
		g_exitcode = 258;
	if (line_lst != NULL)
		delete_t_list(line_lst);
	return (1);
}

void	ft_atexit(void)
{
	system("leaks -q minishell");
}

// struct sigaction create_sigaction(custom_sigaction sa) {
//     struct sigaction action;
//     action.sa_handler = sa.handler;
//     action.sa_mask = sa.mask;
//     action.sa_flags = sa.flags;
//     return action;
// }

	// signal(SIGINT, signal_int);   // Handle Ctrl-C
	// signal(SIGQUIT, signal_handler);  // Handle Ctrl-'/'
	// 
int	main(int argc, char *argv[], char **original_envp)
{
	char		*line;
	t_envp		*envp;
	if (argc != 1)
		return (printf("%s not started right", argv[0]));

	// struct sigaction sa;
    // sa.sa_handler = sigintHandler;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;
	// if (sigaction(SIGINT, &sa, NULL) == -1) {
    //     perror("sigaction");
    //     exit(1);
    // }
	// signals_controller();
	// signal(SIGQUIT, signal_bs);
	envp = copy_envp(original_envp);
	g_exitcode = 0;
	while (1)
	{	
		// disable_ctrl_c_display();
	// t_custom_sigaction sa = init_sa(tempHandler);	
    // struct sigaction action = create_sigaction(sa);

    // if (sigaction(SIGINT, &action, NULL) == -1) {
    //     perror("sigaction");
    //     return 1;
    // }
		line_reader(&line, "minishell$ ");
		if (line != NULL)
		{
			if (!ft_strncmp(line, "exit", 4) || !ft_strncmp(line, "make", 4))
			{
				free(line);
				exit(1);
			}
			enable_ctrl_c_display();
			shell(line, envp);
			free(line);
		}
	}
	return (0);
}
