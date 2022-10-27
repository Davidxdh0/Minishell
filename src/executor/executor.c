/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:08:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/27 16:26:55 by dyeboa        ########   odam.nl         */
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

void	message_exit(char *message, int errornumber)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(errornumber);
}

void	message(char *msg)
{
	ft_putstr_fd(msg, 2);
}

// execute commands op basis van wat het is. 
void	execute_commands(t_line_lst *stack, t_data *data, int stdin, int stdout, char **envp)
{
	pid_t	pid1;

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
		waitpid(pid, ?, ?)
;	}
}

void	execute_process(t_line_lst *cmdlist, char **envp, int fd[2], t_data *data)
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

void	execute_builtins(t_line_lst *cmdlist)
{
	//check testers voor alle builtins.
	if (!cmdlist)
		return ;
	if (cmdlist->type == 0)
		execute_cd(cmdlist);
	if (cmdlist->type == 1)
		execute_file(cmdlist);
	if (cmdlist->type == 2)
		execute_file(cmdlist);
	if (cmdlist->type == 3)
		execute_text(cmdlist);
	if (cmdlist->type == 4)
		execute_var(cmdlist);
}
