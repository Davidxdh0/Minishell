/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 16:10:39 by bramjr        #+#    #+#                 */
/*   Updated: 2021/05/27 17:56:43 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
**		Part of the ascii table
** ====================================	**
**  9 = '\t' ht	(TAB)	horizontal tab	**
** 10 = '\n' nl	(LF)	newline			**
** 11 = '\v' vt	(VT)	vertical tab	**
** 12 = '\f' np	(FF)	feed			**
** 13 = '\r' cr	(CR)	carriage return	**
** 32 = ' '	 sp	(SP)	space			**
** ====================================	**
*/

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
