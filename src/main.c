/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 07:28:42 by bprovoos      ########   odam.nl         */
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

// char	*rl_gets(char *line_read, const char *display_name)
// {
// 	if (line_read)
// 	{
// 		free (line_read);
// 		line_read = (char *) NULL;
// 	}
// 	line_read = readline (display_name);
// 	if (line_read && *line_read)
// 		add_history (line_read);
// 	return (line_read);
// }

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
	// char	*line;

	while (1)
	{
		set_promt();
		// line = NULL;
		// line = rl_gets(line, "$");
		// line.size = 0;
		// line.str = "123";
		get_input_line(&line);
		lexer(&line, &line_lst);
		printf("[line]\t%s[nread]\t%zi\n[size]\t%zu\n", \
			line.str, line.nread, line.size);
	}
	return (0);
}
