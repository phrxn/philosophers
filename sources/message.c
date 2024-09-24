/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:03:33 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/09 21:38:45 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	printf_philo_status(time_t time, t_uint id, t_status status)
{
	if (status == TAKE_FORK)
		printf("%ld %d has taken a fork\n", time, id);
	else if (status == EATING)
		printf("%ld %d is eating\n", time, id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", time, id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", time, id);
	else if (status == DIED)
		printf("%ld %d died\n", time, id);
}

void	printf_philo(t_philo *philo, time_t time, t_status status, int is_monit)
{
	pthread_mutex_lock(&philo->table->mtx_write);
	if (is_simulation_running(philo->table) == FALSE && is_monit == FALSE)
	{
		pthread_mutex_unlock(&philo->table->mtx_write);
		return ;
	}
	printf_philo_status(time, philo->id, status);
	pthread_mutex_unlock(&philo->table->mtx_write);
}

/**
 * Print a fatal error in STDIN and return 1.
 *
 * @msg: a string with the error message.
 *
 * Return: this method always returns 1.
*/
int	fatal_error(char *msg)
{
	printf("philo fatal error: [%s]\n", msg);
	return (1);
}
