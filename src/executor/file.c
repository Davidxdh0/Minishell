/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 14:35:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/27 16:09:30 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../main/main.h"

void	open_infile(char *file, t_data *data)
{
	int fd;

	fd = -1;
	if (!file)
		return ;
	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		message_exit("open_infile faalt", 1);
	data->infile = fd;
}

void	open_outfile(char *file, t_data *data)
{
	int fd;

	fd = -1;
	if (!file)
		return ;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		message_exit("open_outfile faalt", 1);
	data->outfile = fd;
}