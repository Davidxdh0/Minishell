/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:26 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/26 18:59:03 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "../../libs/libft/libft.h"

char		**lexer(char *line);
char		*get_data_in_quotes(char *str);
char		*get_variable(char *str);

#endif
