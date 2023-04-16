/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:56 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/04/14 13:56:15 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* sources
Example:
https://github.com/yabtaour/Minishell-42
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
# include "../../libs/libft/libft.h"
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct s_line_lst
{
	int					type;
	char				*value;
	int					len;
	int					state;
	struct s_line_lst	*next;
	struct s_line_lst	*prev;
}	t_line_lst;

typedef enum{
	e_start = -1,
	e_cmd,
	e_file,
	e_whitespace,
	e_dquote,
	e_quote,
	e_pipe,
	e_word,			// also flags for commands
	e_var,
	e_redirect_i,
	e_redirect_o,
	e_delimiter,
	e_append
}	note_type;

typedef struct s_data
{
	char	**envp;
	char	**cmd;
	char	*path;
	int 	fd[2];
	int		outfile;
	int 	infile;
	int		exitcode;
}	t_data;

typedef struct s_execute
{
	char	**cmd;
	int		count_cmd; //DCS, can be loaded in during initialization?
	char	**redirects; //redirect zoals gegeven, split op iets, redirects []
	// [<][file]
	// [>][filename]
	struct s_execute *prev;
  	struct s_execute *next;
}	t_execute;

t_data	g_data;


/* Executer  & builtins*/
//executor.c
void	execute_cmd_list(t_line_lst *cmdlist, t_data *data);
void	execute_commands(t_line_lst *stack, t_data *data, char **envp);
void	execute_process(t_line_lst *stack, t_data *data, char **envp);
void	close_fd_dup(t_data *data, int *stin, int *stout);
void	test_lists(t_line_lst *head, char **envp);

void	executor_dcs(t_execute *cmd_struct, char **envp); //DCS
int		ft_heredoc(t_execute *cmd_struct, char **envp, char *eof); //DCS

//errors.c
int		msg_error_code(char *err, int code);
int		msg_error(char *err);
int		msg_custom_error_code(char *err, char *cmd, int code);

//exit.c
void	message_exit(char *message, int errornumber);
void	message(char *msg);
void	message_nl(char *msg);

//paths.c
char	*get_env_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);

//redirect
void    redirect(t_line_lst *stack, t_data *data);

//file.c
void	open_infile(char *file);
void	redir_outfile(char *file, t_data *data, int flag);
void    redirect(t_line_lst *stack, t_data *data);

//builtin.c
void	execute_builtin(t_line_lst *cmdlist, char **cmd, t_data *data);
int		is_builtin(char *str);

void	ft_pwd(int fd); //DCS
void	ft_echo(t_execute *cmd_struct, int fd); //DCS
bool	ft_env(char **envp, int fd); //DCS
void	ft_cd(t_execute *cmd_struct, char **envp, char *path); //DCS
void	ft_export(char *cmd, char **envp, int fd); //DCS
void	ft_unset(char *cmd, char **envp, int fd); //DCS

//cd.c
void	execute_cd(char **cmd, t_data *data);
void	update_old_pwd(char *oldpath, t_data *data);
void	cd_home(char **envp);
int		change_dir(char *oldpath, char *path);

//echo.c
void	execute_echo(char **cmd);
int		check_option(char **cmd);

//export.c
void	execute_export(char **cmd, t_data *data);
int		check_env_exist(char **cmd, t_data *data);

/* LEXER*/
int			is_valid_type(note_type type, t_line_lst *node);
int			is_valid_var(note_type last_type);
int			is_valid_word(note_type last_type);
int			is_valid_file(note_type last_type);
int			is_valid_pipe(note_type last_type);
int			is_valid_cmd(note_type last_type);
char		*type_to_string(note_type type);
note_type	get_last_type(t_line_lst *node);
int			is_word(char c);

t_line_lst	*lexer(char *line);
t_line_lst	*parser(char *line);
t_line_lst	*fil_list(char *line);

//specialchar.c
int 		space_case(t_line_lst **line_lst, int state);
int			pipe_case(t_line_lst **line_lst, int state);
int			less_than_case(t_line_lst **line_lst, char *line, int state);
int			greater_than_case(t_line_lst **line_lst, char *line, int state);
int			dolar_special_case(t_line_lst **line_lst, char next_char, int state);
int			dolar_sign_case(t_line_lst **line_lst, char *line, int state);

// lexer.c
int			ft_isspecial(char chr);
int			word_case(t_line_lst **line_lst, char *line, int state);
int			quotes(t_line_lst *line_lst, char c, int state);

// expander.c
t_line_lst	*expander(t_line_lst *line_lst);

//grammarchecker.c
int		is_valid_grammer(t_line_lst *head);

/* PARSER
The parser processes the input line and build the list with tokens */
void		delete_t_list(t_line_lst **head);
void		add_at_end_of_list(t_line_lst **head, int type, char *value, int state);
void		show_t_list(t_line_lst *node, char *line);
char		*type_to_string(note_type type);
int			length_of_list(t_line_lst *node);
char 		*make_string(t_line_lst *line_lst);

/* Main */
int		shell(char *line, char **envp);
int		input_is_argv(int argc, char *argv[], char **line);
void	line_reader(char **line, const char *display_name);
void	add_line_in_history(char **line);
int		str_isspaces(char **line);
int	ft_isredirect(char *str);
#endif
