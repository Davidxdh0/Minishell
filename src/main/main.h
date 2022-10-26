/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:55:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 19:09:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* sources
bash flow
http://www.aosabook.org/en/bash.html
tutorial
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
explanation shell:
https://cs61.seas.harvard.edu/site/2019/Section7/
Shell Command Language:
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
BNF:
https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form
bash manual:
https://www.gnu.org/software/bash/manual/

bash parser"
https://mywiki.wooledge.org/BashParser
tokenizer:
https://ix-56h.github.io/how-to-make-a-tokenizer/
ridirections:
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

Unit tester:
https://github.com/Snaipe/Criterion
*/
#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libs/libft/libft.h"
# include "../lexer/lexer.h"
# include "../parser/parser.h"

#define RIDIRECT_I		"<"
#define RIDIRECT_O		">"
#define APPEND			">>"
#define DELIMITER		"<<"
#define SINGLE_QUOTE	"\'"
#define DOUBLE_QUOTE	"\""
#define PIPE			"|"

/* BNF
commandline ::= list
          |  list ";"
          |  list "&"

list     ::=  conditional
          |   list ";" conditional
          |   list "&" conditional

conditional ::=  pipeline
          |   conditional "&&" pipeline
          |   conditional "||" pipeline

pipeline ::=  command
          |   pipeline "|" command

command  ::=  word
          |   redirection
          |   command word
          |   command redirection

redirection  ::=  redirectionop filename
redirectionop  ::=  "<"  |  ">"  |  "<<"  |  ">>"
*/

/* command list
''		should prevent the shell from interpreting the meta- characters in the quoted sequence
""		hould prevent the shell from interpreting the meta- characters in the quoted sequence except for $
|		(pipe) & (fork)
<		(dup2) redirect input
>		(dup2) redirect output
<<		heredoc, repeat reading input and execute command until delimiter?
>>		(dup2) redirect output in append mode
cmd		(execve)
file	(open)
$VAR	expand VAR to the value
$?		expand to the exit status of the most recently executed foreground pipeline
*/
typedef enum{
	cmd,
	file,
	pipe,
	text,
	var,
	redirect
}	note_type;

int			input_is_argv(int argc, char *argv[], char **line);
void		add_line_in_history(char **line);

#endif
