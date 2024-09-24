/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:25:22 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/09 20:48:51 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Converts a number in a string to an int. This method checks if there was
 * an overflow or underflow during the conversion.
 *
 * @number:	a string with number
 * @status: if it isn't a NULL pointer, sets 0 if the conversion went well,
 * 			1 if there was an overflow or underflow. SAVE ANY VALUE inside
 * 			status BEFORE call this function, because the actual value will
 * 			be replaced.
 *
 * Return: a int with the number.
 */
int	ft_atoi(const char *number, int *status)
{
	long	int_to_return;
	char	is_negative;

	is_negative = 1;
	int_to_return = 0;
	if (*number == '-' || *number == '+')
	{
		if (*number == '-')
			is_negative = -1;
		number++;
	}
	while (*number >= '0' && *number <= '9')
	{
		int_to_return = (int_to_return * 10) + (*number++ - '0');
		if ((is_negative == 1 && int_to_return > INT_MAX)
			|| (is_negative == -1 && int_to_return > ((long)INT_MAX + 1)))
		{
			if (status)
				*status = 1;
			return (0);
		}
	}
	if (status)
		*status = 0;
	return (int_to_return * is_negative);
}
