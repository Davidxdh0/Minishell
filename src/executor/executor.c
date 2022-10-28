/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:08:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/28 12:03:46 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../main/main.h"

/* cmd's zijn in linked list -> execute op basis van: links, rechts, type, 
	eerste keer lezen van fd[1] - kan file zijn.
	check type - command/var/cd/pipe/&/>/>&/>>/>>&/</<</
	wachten op pid als het geen background is, anders asynchroon.
	output naar fd[1]
	lezen van fd[1]
	
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

*/

/*

The strategy for your shell is to have the parent process do all the piping and redirection
before forking the processes. In this way the children will inherit the redirection. The parent
needs to save input/output and restore it at the end.
*/

/*
	Have a working history
	Search and launch the right executable (based on the PATH variable or using a
	relative or an absolute path).
	Handle ’ (single quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence.
	Handle " (double quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence except for $ (dollar sign).
	
	""'$variabel'"" - testen
	
	<< should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
	>> should redirect output in append mode
	environment variables ($variabele
	$? laatste exit code

	◦ echo with option -n : -nnnnnn -n -n -n -n -nnn == valid
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or argument
	◦ exit with no options
	met infile en outfile?
	SHLVL
	OLDPWD
	segfault = env checken als dingen leeg zijn.
	expand
	check of env leeg is.
	
	niet: Not interpret unclosed quotes or special characters which are not required by the
	subject such as \ (backslash) or ; (semicolon).
*/


// 4.1. read command table
// 4.x. creating pipes
// 4.x. creating processes

// execute commands op basis van wat het is. 
void	execute_process(t_line_lst *stack, t_data *data, int stdin, int stdout, char **envp)
{
	pid_t	pid1;
	int	wstatus;

	pid1 = fork();
	if (pid1 < 1)
		message_exit("fork went wrong");
	if (pid1 == 0)
	{
		dup2(data->infile, 0);
		dup2(data->outfile, 1);
		if (execve(data->path, data->cmd, envp) == -1)
			perror_exit(1, data->path);
	}
	else
	{
		close(data->fd[1]);
		waitpid(pid2, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit(WEXITSTATUS(wstatus));
	}
}

void	execute_commands(t_line_lst *stack, t_data *data, int stdin, int stdout, char **envp)
{
	char	**splitted_cmd;
	char	*path_and_cmd;

	if (!stack || !data)
		return ;
	// if (stack->type == builtin)
	// 	execute_builtins(stack, data)
	// else if ()

	data->splitted_cmd = ft_split(stack->cmd, ' ');
	data->path = get_cmd_path(splitted_cmd[0], envp);
	if (!data->path || data->splitted_cmd)
		message("geen path of splitted cmd")
	execute_process(stack, &stdin, &stdout, envp, &data)
	if (cmd1[0] == '\0')
		message_exit("cmd1 == '\0'");
	if (ft_isspace(cmd1[0]))
		exit(msg_custom_error_code("pipex: command not found: ", "", 0));
}

void	execute_cmd_list(t_line_lst *cmdlist, char **envp, int fd[2], t_data *data)
{
	t_line_lst *stack;

	int	stin;
	int	stout;

	if (!cmdlist)
		return ;
	stack = cmdlist;
	//while niet last van stack.
	while(stack)
	{
		pipe(fd[2]);
		stdin = dup(0);
		stdout = dup(1);
		execute_commands(stack, &stdin, &stdout, envp, &data);
		stack = stack->next;
	}
}
