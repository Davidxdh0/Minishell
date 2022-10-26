/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:08:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/26 20:06:46 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	◦ >> should redirect output in append mode
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



void	execute_list(t_line_lst *cmdlist)
{
	if (!cmdlist)
		return ;
	if (cmdlist->type == 0)
		//cmd
	if (cmdlist->type == 1)
		//file
	if (cmdlist->type == 2)
		//pipe
	if (cmdlist->type == 3)
		//text
	if (cmdlist->type == 4)
		//var
	if (cmdlist->type == 5)
		//redirect
		
}