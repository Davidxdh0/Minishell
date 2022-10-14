/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:55:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 10:00:31 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* sources
bash manual:
https://www.gnu.org/software/bash/manual/
explanation shell:
https://harm-smits.github.io/42docs/projects/minishell
explanation shell:
https://cs61.seas.harvard.edu/site/2019/Section7/
Shell Command Language:
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
*/
#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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
redirectionop  ::=  "<"  |  ">"  |  "2>"
*/
typedef struct s_line_lst
{
	int					type;
	char				*value;
	struct s_line_lst	*next;
}	t_line_lst;

typedef struct s_line
{
	char	*str;
	size_t	size;
	ssize_t	nread;
}	t_line;

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
	var,
	redirect
}	note_type;

void	lexer(t_line *line, t_line_lst *line_list);

#endif
