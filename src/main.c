/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/13 15:40:52 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
	Print the promt in the terminal.
*/
void	set_promt(void)
{
	printf("minishell$ ");
}

/*
	Reading the input line form the terminal.
*/
void	get_input_line(t_line *line)
{
		line->str = NULL;
		line->nread = getline(&line->str, &line->size, stdin);
}

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

To do
[ ] Header dependency in makefile
*/
int	main(void)
{
	t_line		line;
	t_line_lst	line_lst;

	while (1)
	{
		set_promt();
		get_input_line(&line);
		lexer(&line, &line_lst);
		printf("[line]\t%s[nread]\t%zi\n[size]\t%zu\n", \
			line.str, line.nread, line.size);
	}
	return (0);
}
