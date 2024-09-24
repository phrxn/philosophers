/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:20:27 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/12 16:21:52 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * This method is used when there is only one philosopher thread.
 *
 * @philo: a pointer to philosopher struct
*/
void	*alone(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_forks[philo->forks[0]]);
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		TAKE_FORK, FALSE);
	sleep_in_ms(philo->table, philo->table->time_to_die);
	pthread_mutex_unlock(&philo->table->mtx_forks[philo->forks[0]]);
	return (NULL);
}
