/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:54:04 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/27 15:49:48 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libs/libft/libft.h"
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
	int		infile;
	int		outfile;
	int		fd[2];
}	t_data;

#endif