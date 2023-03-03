// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   lexer.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/03/03 15:20:47 by dyeboa        #+#    #+#                 */
// /*   Updated: 2023/03/03 15:34:18 by dyeboa        ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../main/main.h"

// t_line_lst	*lexer(char *line)
// {
// 	t_line_lst	*head;

// 	head = fil_list(line);
// 	// check if list is valid
// 	return (head);
// }

// t_line_lst	*parser(char *line)
// {
// 	t_line_lst	*head;

// 	head = fil_list(line);
// 	// check if list is valid
// 	return (head);
// }


// t_line_lst	*fil_list(char *line)
// {
// 	t_line_lst	*head;
// 	note_type	last_type;
// 	int			i;
// 	int			len;

// 	i = 0;
// 	head = NULL;
// 	//line = ft_strtrim(line, " ");
// 	while (line[i])
// 	{
// 		last_type = get_last_type(head);

// 		if (line[i] == '|')
// 			add_at_end_of_list(&head, e_pipe, "|");
// 		else if (line[i] == '"')
// 			add_at_end_of_list(&head, e_dquote, "\"");
// 		else if (line[i] == ' ')
// 			add_at_end_of_list(&head, e_whitespace, " ");
// 		else if (line[i] == '<')
// 		{
// 			i++; 
// 			if (line[i] != '<')
// 			{
// 				add_at_end_of_list(&head, e_redirect_i, "<");
// 				continue;
// 			}
// 			add_at_end_of_list(&head, e_delimiter, "<<");
// 		}	
// 		else if (line[i] == '>')
// 		{
// 			i++;
// 			if (line[i] != '>')
// 			{
// 				add_at_end_of_list(&head, e_redirect_o, ">");
// 				continue;
// 			}	
// 			add_at_end_of_list(&head, e_append, ">>");
// 		}
// 		else if (line[i] == '$')
// 		{
// 			i++;
// 			if (line[i] == '?')
// 			{
// 				add_at_end_of_list(&head, e_var, "$?");
// 				i++;
// 				continue;
// 			}
// 			if (line[i] == '$')
// 			{
// 				add_at_end_of_list(&head, e_var, "$$");
// 				i++;
// 				continue;
// 			}	
// 			len = 0;
// 			while (line[i + len] && ft_isascii(line[i + len]) && line[i + len] != ' ')
// 				len++;
// 			add_at_end_of_list(&head, e_var, ft_substr(line, i, len));
// 			i += len - 1;
// 		}
// 		else if (ft_isascii(line[i]) && line[i] != ' ')
// 		{
// 			len = 0;
// 			while (line[i + len] && ft_isascii(line[i + len]) && line[i + len] != ' ')
// 				len++;
// 			if (last_type == e_start || last_type == e_pipe)
// 				add_at_end_of_list(&head, e_word, ft_substr(line, i, len));
// 			if (last_type == e_cmd || last_type == e_word || last_type == e_delimiter ||  last_type == e_whitespace)
// 				add_at_end_of_list(&head, e_word, ft_substr(line, i, len));
// 			if (last_type == e_redirect_i || last_type == e_redirect_o || last_type == e_append)
// 				add_at_end_of_list(&head, e_file, ft_substr(line, i, len));
// 			if (line[i + len] != ' ')
// 				len++;
// 			i += len - 1;
// 		}
// 		i++;
// 	}
// 	return (head);
// }