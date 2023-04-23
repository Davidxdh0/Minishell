/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_dcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:44:49 by abarteld      #+#    #+#                 */
/*   Updated: 2023/04/09 18:44:50 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static int	ft_exit_error(char *str, int err)
{
	printf("Error\n%s\n", str);
	exit (err);
}

// make ft_strcmp_exact
int	ft_heredoc(t_execute *cmd_struct, char **envp, char *eof)
{
printf("\nHere In This DOC\n");
	char	*line;
	int		len;
	int		fd;

	// eof will end up being in the struct
	line = NULL;
	len = ft_strlen(eof);
	fd = open(".heredoc", O_CREAT, 0644);
	if (fd < 0)
		ft_exit_error("Heredoc Tempfile Create Error", 16);
	while (!line || ft_strncmp(line, eof, len))
	{
		free(line);
		line = readline("HereDoc> ");
		if (!line)
			ft_exit_error("Readline Error", 17);
		// Put shit in file
		// ft_putstr_fd(line, fd);
	}
	// close(fd);
	unlink(".heredoc"); // relocate this unlink
	return (fd);
printf("\nFuck this DOC, I'm Out\n");
}
