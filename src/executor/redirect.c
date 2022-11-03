/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 11:36:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/03 13:58:05 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void    execute_redirect(t_line_lst *stack, t_data *data)
{
    int status;
    t_line_lst *temp;

    temp = stack;
    while(temp->type != PIPE)
    {
        if (temp->type == RIDIRECT_I)
            open_infile(temp->value, data);
        // if (temp->type == DELIMITER)
        //     open_till(temp->value, data, temp->next->value);
        if (temp->type == RIDIRECT_O || temp->type == APPEND)
             open_outfile(temp->value , data, temp->type);
    }
}