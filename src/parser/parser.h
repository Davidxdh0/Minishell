/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 21:41:10 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/05/28 21:50:24 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_execute
{
	char	**cmd;
	char	**redirects; //redirect zoals gegeven, split op iets, redirects
	int		count_cmd; //DCS, can be loaded in during initialization?
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
t_execute *acco(t_execute *cmds);
void copy_commands_and_redirects(t_execute *dest_node, char **cmd_list, int num_redirects);
t_execute *create_new_node(int num_commands, int num_redirects);
int count_redirects(char **cmd_list);
int ft_arrlen(char **arr);