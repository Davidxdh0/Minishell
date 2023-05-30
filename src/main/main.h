/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:56 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/30 15:35:18 by dyeboa        ########   odam.nl         */
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
# include <readline/readline.h>
# include "../../libs/libft/libft.h"
# include <termios.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <string.h>
# include <errno.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../parser/parser.h"

int		g_exitcode;

// typedef struct s_line_lst
// {
// 	int					type;
// 	char				*value;
// 	int					len;
// 	int					state;
// 	struct s_line_lst	*next;
// 	struct s_line_lst	*prev;
// }	t_line_lst;

typedef enum{
	e_start = 0,
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
}	node_type;

typedef enum builtin_names
{
	ECH = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	e_builtin_names;

// typedef struct s_data
// {
// 	char	**envp;
// 	char	**cmd;
// 	char	*path;
// 	int 	fd[2];
// 	int		outfile;
// 	int 	infile;
// 	int		exitcode;
// }	t_data;

typedef	struct s_envp
{
	struct s_envp	*head;
	char			*line;
	int				value;
	char			*identifier;
	char			*string;
	struct s_envp	*prev;
	struct s_envp	*next;
}	t_envp;


// typedef struct s_execute
// {
// 	char	**cmd;
// 	char	**redirects; //redirect zoals gegeven, split op iets, redirects []
// 	int		count_cmd; //DCS, can be loaded in during initialization?
// 	char	*heredoc_name;
// 	struct s_execute *prev;
//   	struct s_execute *next;
// }	t_execute;

/* Executer  & builtins*/
//executor.c
// void	execute_cmd_list(t_line_lst *cmdlist, t_data *data);
// void	execute_commands(t_line_lst *stack, t_data *data, char **envp);
// void	execute_process(t_line_lst *stack, t_data *data, char **envp);
// void	close_fd_dup(t_data *data, int *stin, int *stout);
// void	test_lists(t_line_lst *head, char **envp);

// //errors.c
// int		msg_error_code(char *err, int code);
// int		msg_error(char *err);
// int		msg_custom_error_code(char *err, char *cmd, int code);

// //exit.c
// void	message_exit(char *message, int errornumber);
// void	message(char *msg);
// void	message_nl(char *msg);

// //paths.c
// char	*get_env_paths(char **envp);
// char	*get_cmd_path(char *cmd, char **envp);

// //redirect
// void    redirect(t_line_lst *stack, t_data *data);

// //file.c
// void	open_infile(char *file);
// void	redir_outfile(char *file, t_data *data, int flag);
// void    redirect(t_line_lst *stack, t_data *data);

// //builtin.c
// void	execute_builtin(t_line_lst *cmdlist, char **cmd, t_data *data);
// int		is_builtin(char *str);

// //cd.c
// void	execute_cd(char **cmd, t_data *data);
// void	update_old_pwd(char *oldpath, t_data *data);
// void	cd_home(char **envp);
// int		change_dir(char *oldpath, char *path);

// //echo.c
// void	execute_echo(char **cmd);
// int		check_option(char **cmd);

// //export.c
// void	execute_export(char **cmd, t_data *data);
// int		check_env_exist(char **cmd, t_data *data);

/* LEXER*/
int			is_valid_type(node_type type, t_line_lst *node);
int			is_valid_var(node_type last_type);
int			is_valid_word(node_type last_type);
int			is_valid_file(node_type last_type);
int			is_valid_pipe(node_type last_type);
int			is_valid_cmd(node_type last_type);
char		*type_to_string(node_type type);
node_type	get_previous_type(t_line_lst *node);
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
void 		delete_node(t_line_lst *node_to_delete);
t_line_lst	*remove_whitespace_list(t_line_lst *line_lst);
t_line_lst	*word_list(t_line_lst *line);
t_line_lst	*whitespaces_list(t_line_lst *line);
t_line_lst	*string_quotes(t_line_lst *line_lst);
char		*ft_getenv(const char *name, char **envp);
int 		find_variable(char *str);
t_line_lst	*variable_expand(t_line_lst *line, char **envp);
char 		*change_str(char *str, int begin, int eind, char **envp);\

//grammarchecker.c
int			is_valid_grammer(t_line_lst *head);

/* PARSER
The parser processes the input line and build the list with tokens */
void		delete_t_list(t_line_lst *head);
void		add_at_end_of_list(t_line_lst **head, int type, char *value, int state);
void		show_t_list(t_line_lst *node, char *line);
char		*type_to_string(node_type type);
int			length_of_list(t_line_lst *node);
char 		*make_string(t_line_lst *line_lst);
int			syntax_check(t_line_lst *line);
void 		delete_node(t_line_lst *node_to_delete);


//signals.c
void	redirect_signal(int signal);

/* Main */
int		shell(char *line, char **original_envp, t_envp *envp); //DCS (still need to get rid of original envp?)
int		input_is_argv(int argc, char *argv[], char **line);
void	line_reader(char **line, const char *display_name);
void	add_line_in_history(char **line);
int		str_isspaces(char **line);
int		ft_isredirect(char *str);
void	show(t_execute *cmd);
int		count_commands(t_line_lst *head);


//util
int		perror_return(char *msg, char *msg2);
void	delete_t_exec(t_execute *head);

// Executor
void	executor_dcs(t_execute *cmd_struct, t_envp *envp);
void	ft_execute_cmd(t_execute *cmd_struct, t_envp *envp);
void	ft_single_command(t_execute *cmd_struct, t_envp *envp);
// Builtins
int		check_builtin(char *arg);
void	exec_builtin(t_execute *cmd_struct, t_envp *envp, int fd);

bool	ft_cd(t_execute *cmd_struct, t_envp *envp);
void	ft_echo(t_execute *cmd_struct, int fd);
bool	ft_env(t_envp *envp, int fd);
void	ft_exit(t_execute *cmd_struct);
void	ft_export(t_execute *cmd_struct, t_envp *envp, int fd);
void	ft_export_cmd(char *cmd, char *target, t_envp *envp, int fd);
void	ft_export_argless(t_execute *cmd_struct, t_envp *envp, int fd);
void	ft_pwd(int fd);
void	ft_unset(t_execute *cmd_struct, t_envp *envp, int fd); //might not need fd

void	builtin_infile(char **list);
bool	builtin_outfile(char **list, int *fd);
bool	long_atoi(const char *str, long *number);
// Utils
int		ft_exit_error(char *str, int err);
void	ft_perror(char *str, int);
void	*ft_malloc(size_t size);

bool	redirect_infile(char **list, char *name);
bool	redirect_outfile(char **list);

char	*get_path(char *exec_argv, char **path);
char	*check_path(char *exec_argv, char **envp);
char	*find_command(char **path, char *basepath);
char	*ft_getenv(const char *name, char **envp);
bool	ft_getenv_int(int *env, const char *name, char **envp);
bool	is_path(char *exec_argv);

//HereDoc
void	ft_heredoc_init(t_execute *cmd_struct);
bool	ft_heredoc(char *eof, char *name);
void	ft_heredoc_name(t_execute *cmd_struct, int cmd_nbr);
void	ft_heredoc_cleanup(t_execute *cmd_struct);

//Envp
t_envp	*copy_envp(char **original_envp);
char	**envp_to_array(t_envp *envp);
int		check_envp_value(char *str);


//Syntax
int		syntax_pipe(t_line_lst *line);
int		syntax_redirects(t_line_lst *line);
int		syntax_quotes(t_line_lst *line, node_type type);
int		syntax_count_quotes(t_line_lst *line);

//util
int	perror_return(char *msg, char *msg2);
void	delete_t_exec(t_execute *head);

#endif
// // Executor
// void	executor_dcs(t_execute *cmd_struct, char **envp);
// void	ft_execute_cmd(t_execute *cmd_struct, char **envp);
// // void	ft_execute_command(t_execute *cmd_struct, char **envp, int pipe1[2], int pipe2[2]);
// // void	ft_execute_command_struct(t_execute *cmd_struct, char **envp);
// void	ft_single_command(t_execute *cmd_struct, char **envp);
// // Builtins
// int		check_builtin(char *arg);
// void	exec_builtin(t_execute *cmd_struct, char **envp, int fd);

// void	ft_cd(t_execute *cmd_struct, char **envp, char *path);
// void	ft_echo(t_execute *cmd_struct, int fd);
// bool	ft_env(char **envp, int fd);
// void	ft_exit(t_execute *cmd_struct, char **envp);
// void	ft_export(t_execute *cmd_struct, char **envp, int fd);
// void	ft_export_cmd(char *cmd, char **envp, int fd);
// void	ft_export_argless(t_execute *cmd_struct, char **envp, int fd);
// void	ft_pwd(int fd);
// void	ft_unset(t_execute *cmd_struct, char **envp, int fd);

// void	builtin_infile(char **list);
// bool	builtin_outfile(char **list, int *fd);
// // Utils
// int		ft_exit_error(char *str, int err);

// bool	redirect_infile(char **list, char *name);
// bool	redirect_outfile(char **list);

// char	*get_path(char *exec_argv, char **path);
// char	*check_path(char *exec_argv, char **envp);
// char	*find_command(char **path, char *basepath);
// char	*ft_getenv(const char *name, char **envp);
// bool	ft_getenv_int(int *env, const char *name, char **envp);
// bool	is_path(char *exec_argv);

// //HereDoc
// void	ft_heredoc_init(t_execute *cmd_struct);
// bool	ft_heredoc(char *eof, char *name);
// void	ft_heredoc_name(t_execute *cmd_struct, int cmd_nbr);
// void	ft_heredoc_cleanup(t_execute *cmd_struct);