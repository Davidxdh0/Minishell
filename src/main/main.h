/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:55:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/27 17:01:52 by bprovoos      ########   odam.nl         */
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
commandline ::= pipeline

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

/* Program flow
1. lexer
1.1. check syntax
1.2. puts the characters together into words called tokens
2. parser
2.1. read the tokens
2.2. build the command table
-------(index, command, flags, envp)
-------(in, out, err)
3. expander
4. executor
4.1. read command table
4.x. creating pipes
4.x. creating processes

To do:
[X] Header dependency in makefile
[X] Creata a flag option for giving command through argv
[ ] Make unit testers

Optional:
[ ] *.d files in seperate folder
*/
int		shell(char *line, char **envp);
int		input_is_argv(int argc, char *argv[], char **line);
void	line_reader(char **line, const char *display_name);
void	add_line_in_history(char **line);

#endif
