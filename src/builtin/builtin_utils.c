/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: abarteld <abarteld@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 10:36:17 by abarteld      #+#    #+#                 */
/*   Updated: 2023/05/04 10:36:20 by abarteld      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static unsigned long long	string_to_ull(const char *str, bool neg)
{
	unsigned long long	atoi;

	atoi = 0;
	while (*str >= '0' && *str <= '9')
	{
		atoi *= 10;
		atoi += *str - 48;
		str++;
		if ((atoi > __LONG_LONG_MAX__) && (neg == false))
			return ((unsigned long long)__LONG_LONG_MAX__ + 2);
		if ((atoi > (unsigned long long)__LONG_LONG_MAX__ + 1) && (neg == true))
			return ((unsigned long long)__LONG_LONG_MAX__ + 3);
	}
	return (atoi);
}

bool	long_atoi(const char *str, long *number)
{
	unsigned long long	atoi;
	bool				neg;

	neg = false;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = true;
		str++;
	}
	atoi = string_to_ull(str, neg);
	if (atoi > (unsigned long long)__LONG_LONG_MAX__ + 1 || \
		(atoi > __LONG_LONG_MAX__ && neg == 0))
		return (false);
	if (atoi == (unsigned long long)__LONG_LONG_MAX__ + 1)
		*number = (__LONG_LONG_MAX__ * -1) - 1;
	else
	{
		*number = (long)atoi;
		if (neg == true)
			atoi *= -1;
	}
	return (true);
}
