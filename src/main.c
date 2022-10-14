/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 11:24:39 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_input_line(char *line_read, const char *display_name)
{
	if (line_read)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	line_read = readline (display_name);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
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

To do:
[X] Header dependency in makefile

Optional:
[ ] *.d in seperate folder
*/
int	main(void)
{
	static char	*line;
	char		*tokens;

	while (1)
	{
		line = get_input_line(line, "minishelll$ ");
		lexer(line, &tokens);
	}
	return (0);
}
