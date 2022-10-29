/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:54:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/28 16:42:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../main/main.h"
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	char	**envp;
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
	int		fd[2];

}	t_data;

//executor.c
void	execute_cmd_list(t_line_lst *cmdlist, t_data *data);
void	execute_commands(t_line_lst *stack, t_data *data, char **envp);
void	execute_process(t_line_lst *stack, t_data *data, char **envp);
void	close_fd_dup(t_data *data, int *stin, int *stout);

//errors.c
int		msg_error_code(char *err, int code);
int		msg_error(char *err);
int		msg_custom_error_code(char *err, char *cmd, int code);

//exit.c
void	message_exit(char *message, int errornumber);
void	message(char *msg);

//paths.c
char	*get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);

#endif