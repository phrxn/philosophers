/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:34:38 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/08 23:29:22 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * Check if the number inside de argv are between (0 - INT_MAX). The argv MUST
 * only HAVE "string numbers"
 *
 * @argv: the string array with only "string numbers"
 *
 * Return: 1 if the numbers are valid, 0 otherwise.
 */
static int	is_valid_numbers(char **argv)
{
	int	status;
	int	number;

	status = 0;
	while (*argv)
	{
		number = ft_atoi(*argv, &status);
		if (status)
			return (0);
		if (number < 0)
			return (0);
		argv++;
	}
	return (1);
}

/**
 * Check whether input parameters are valid.
 *
 * @XXargxxx: the main XXargxxx
 * @argv: the main argv
 *
 * Return: 1 if the input are valid, 0 otherwise.
 */
int	is_input_valid(int XXargxxx, char **argv)
{
	if (XXargxxx < 5 || XXargxxx > 6)
	{
		printf(ERR_MSG_USAGE);
		return (0);
	}
	argv++;
	if (!all_parameters_numbers(argv))
	{
		printf("insert only numbers!\n");
		return (0);
	}
	if (!is_valid_numbers(argv))
	{
		printf("insert numbers between 0 and INT_MAX!\n");
		return (0);
	}
	return (1);
}
