/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:49:40 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/14 19:26:38 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_forks[philo->forks[0]]);
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		TAKE_FORK, FALSE);
	pthread_mutex_lock(&philo->table->mtx_forks[philo->forks[1]]);
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		TAKE_FORK, FALSE);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->mtx_forks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->mtx_forks[philo->forks[1]]);
}

static void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->mtx_time_last_eat);
	philo->time_last_eat = get_time_ms();
	pthread_mutex_unlock(&philo->mtx_time_last_eat);
	if (philo->table->must_eat_for_time > 0)
	{
		pthread_mutex_lock(&philo->mtx_count_eat);
		philo->count_eat++;
		pthread_mutex_unlock(&philo->mtx_count_eat);
	}
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		EATING, FALSE);
	sleep_in_ms(philo->table, philo->table->time_to_eat);
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		SLEEPING, FALSE);
	drop_forks(philo);
}

static void	think(t_philo *philo)
{
	time_t	time_to_sleep;

	time_to_sleep = (philo->table->time_to_die - philo->table->time_to_eat
			- (get_time_ms() - philo->time_last_eat));
	if (time_to_sleep < 0)
			time_to_sleep = 0;
	if (time_to_sleep == 0)
			time_to_sleep = 1;
	if (time_to_sleep > 500)
			time_to_sleep = 100;
	printf_philo(philo, get_time_ms() - philo->table->clock_time,
		THINKING, FALSE);
	sleep_in_ms(philo->table, time_to_sleep);
}

/**
 * The philosophers' threads routine.
 *
 * @arg:	a pointer to philosopher struct
*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->must_eat_for_time == 0 || philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->philos_number == 1)
		return (alone(philo));
	while (is_simulation_running(philo->table))
	{
		eat(philo);
		sleep_in_ms(philo->table, philo->table->time_to_sleep);
		think(philo);
	}
	return (NULL);
}
