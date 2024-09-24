/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:32:39 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/12 14:48:59 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Check if the string has only digits.
 *
 * Return: 1 if string has only digits, 0 otherwise.
 */
static int	is_only_digits(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/**
 * Check if all string inside a array are digits.
 *
 * @number_list: the array list with string numbers
 *
 * Return: 	1 if all parameters are numbers, 0 if any item in the list has no
 * 			number or the list is empty.
 */
int	all_parameters_numbers(char **number_list)
{
	if (!number_list || !*number_list)
		return (0);
	while (*number_list)
	{
		if (is_only_digits(*number_list))
			number_list++;
		else
			return (0);
	}
	return (1);
}
