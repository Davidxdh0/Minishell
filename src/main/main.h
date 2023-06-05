/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 15:25:56 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/06/05 15:35:02 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* sources
Unit tester:
https://github.com/Snaipe/Criterion
*/
#ifndef MAIN_H
# define MAIN_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
#include <limits.h>
# include "../parser/parser.h"
# include "../../libs/libft/libft.h"

int		g_exitcode;

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

typedef	struct s_envp
{
	char			*line;
	int				value;
	char			*identifier;
	char			*string;
	struct s_envp	*prev;
	struct s_envp	*next;
}	t_envp;

typedef struct s_execute
{
	char	**cmd;
	char	**redirects;
	int		count_cmd;
	char	*heredoc_name;
	struct s_execute *prev;
  	struct s_execute *next;
}	t_execute;

typedef struct s_line_lst
{
	int					type;
	char				*value;
	int					len;
	int					state;
	struct s_line_lst	*next;
	struct s_line_lst	*prev;
}	t_line_lst;

//parser_util2.c
char **make_redirects(t_line_lst *line_lst);
t_execute *alloc_execute_list(t_line_lst *head);
char *make_string(t_line_lst *line_lst);

//parser_util.c
t_execute 	*acco(t_execute *cmds);
void 		copy_commands_and_redirects(t_execute *dest_node, char **cmd_list, int num_redirects);
t_execute 	*create_new_node(int num_commands, int num_redirects);
int 		count_redirects(char **cmd_list);
int 		ft_arrlen(char **arr);

/* LEXER*/
// int			is_valid_type(node_type type, t_line_lst *node);
// int			is_valid_var(node_type last_type);
// int			is_valid_word(node_type last_type);
// int			is_valid_file(node_type last_type);
// int			is_valid_pipe(node_type last_type);
// int			is_valid_cmd(node_type last_type);
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
int			quotes(t_line_lst **line_lst, char c, int state, int flag);

// expander.c
void 		delete_node(t_line_lst *node_to_delete);
t_line_lst	*remove_whitespace_list(t_line_lst *line_lst);
t_line_lst	*word_list(t_line_lst *line);
t_line_lst	*whitespaces_list(t_line_lst *line);
t_line_lst	*string_quotes(t_line_lst *line_lst);
char		*ft_getenv(const char *name, char **envp);
int 		find_variable(char *str);
t_line_lst	*variable_expand(t_line_lst *line, t_envp *new_envp);
char 		*change_str(char *str, int begin, int eind, t_envp* envp);

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
void signal_int(int signal);
void signal_int_heredoc(int signal);
void 	disable_ctrl_c_display();
void 	enable_ctrl_c_display();
void	signal_bs(int signal);
/* Main */
int		shell(char *line, t_envp *envp); //DCS (still need to get rid of original envp?)
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
t_envp	*executor_dcs(t_execute *cmd_struct, t_envp *envp);
void	ft_execute_cmd(t_execute *cmd_struct, t_envp *envp);
t_envp	*ft_single_command(t_execute *cmd_struct, t_envp *envp);
void	ft_multiple_commands(t_execute *cmd_struct, t_envp *envp);
//Daycare
void		first_child(int *pipe, t_execute *cmd_struct, t_envp *envp);
void		middle_child(int *pipe_in, int *pipe_out, t_execute *cmd_struct, t_envp *envp);
void		last_child(int *pipe, t_execute *cmd_struct, t_envp *envp);
t_execute	*middle_child_loop(t_execute *cmd_struct, t_envp *envp, int **pipes, int *pid);
void		child_cleanup(t_execute *cmd_struct, int **pipes, int *pid, int i);
// Execve Utils
char	*get_path(char *exec_argv, char **path);
char	*check_path(char *exec_argv, char **envp);
char	*find_command(char **path, char *basepath);
char	*ft_getenv(const char *name, char **envp);
bool	is_path(char *exec_argv);

// Builtins
int		check_builtin(char *arg);
t_envp	*exec_builtin(t_execute *cmd_struct, t_envp *envp, int fd);
// Builtin Redirects
bool	builtin_infile(char **list);
bool	builtin_outfile(char **list, int *fd, int i, int temp_fd);
// Builtin Functions
void	ft_cd(t_execute *cmd_struct, t_envp *envp);
void	ft_echo(t_execute *cmd_struct, int fd);
void	ft_env(t_envp *envp, int fd);
void	ft_exit(t_execute *cmd_struct);
t_envp	*ft_export(t_execute *cmd_struct, t_envp *envp, int fd);
void	ft_pwd(int fd);
t_envp	*ft_unset(t_execute *cmd_struct, t_envp *envp);

// Builtin Utils
bool	export_targeted(char *cmd, char *target, t_envp *envp);
t_envp	*ft_export_cmd(char *cmd, char *target, t_envp *envp);
bool	long_atoi(const char *str, long *number);

// Redirects
bool	redirect_infile(char **list, char *name);
bool	redirect_outfile(char **list);
// HereDoc
void	ft_heredoc_init(t_execute *cmd_struct);
void	ft_heredoc(char *eof, char *name);
void	ft_heredoc_name(t_execute *cmd_struct, int cmd_nbr);
void	ft_heredoc_cleanup(t_execute *cmd_struct);

// Envp
t_envp	*copy_envp(char **original_envp);
t_envp	*envp_start_list(char *str);
void	envp_add_node(t_envp *envp, char *str);
t_envp	*remove_envp_node(t_envp *envp);
char	**envp_to_array(t_envp *envp);
// Envp Utils
int		check_envp_value(char *str);
bool	increase_shlvl(t_envp *envp);
// void	show_envp_struct(t_envp *envp);
// void	show_envp_node(t_envp *envp);
char	*get_new_env(char *value, t_envp *envp);
int		count_words_expander(char *value);
int 	find_variable(char *str);

// Utils
int		ft_perror(char *str, int err);
void	*ft_malloc(size_t size);
char	**free_char_array(char **arr);

//Syntax
int		syntax_pipe(t_line_lst *line);
int		syntax_redirects(t_line_lst *line);
int		syntax_quotes(t_line_lst *line, node_type type);
int		syntax_count_quotes(t_line_lst *line);

//util
int			perror_return(char *msg, char *msg2);
void	delete_t_exec(t_execute *head);

#endif