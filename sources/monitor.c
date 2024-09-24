/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:22:41 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/12 14:57:01 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Check if any philosophers have died. This method goes through all the
 * philosophers and checks the time of each one's last meal. If the time of
 * the philosopher's last meal compared to the current time is longer than
 * the time to die, he is considered dead. If any philosopher has died, the
 * simulation stops and information about the philosopher is printed.
 *
 * @table:	the table struct containing all the program variables.
 *
 * Return: TRUE if all philosophers are alive, FALSE otherwise.
 *
*/
static int	all_philo_alive(t_table *table)
{
	t_uint	count_philo;
	int		all_alive;
	t_philo	*philo;
	time_t	time_now;

	count_philo = 0;
	all_alive = TRUE;
	while (count_philo < table->philos_number)
	{
		philo = &table->philos[count_philo];
		pthread_mutex_lock(&philo->mtx_time_last_eat);
		time_now = get_time_ms();
		if ((time_now - philo->time_last_eat) >= table->time_to_die)
		{
			set_simulation_status(table, FALSE);
			printf_philo(philo, time_now - table->clock_time, DIED, TRUE);
			all_alive = FALSE;
		}
		pthread_mutex_unlock(&philo->mtx_time_last_eat);
		if (!all_alive)
			break ;
		count_philo++;
	}
	return (all_alive);
}

/**
 * Check if all the philosophers ate the minimum necessary. If yes, stop the
 * simulation. If yes, the simulation is stopped.
 *
 * @table:	the table struct containing all the program variables.
 *
 * Return: TRUE if all the philosophers ate, FALSE otherwise.
 */
static int	all_philo_eating(t_table *table)
{
	t_uint	count_philo;
	int		all_eat;
	t_philo	*philo;

	count_philo = 0;
	all_eat = TRUE;
	while (count_philo < table->philos_number)
	{
		philo = &table->philos[count_philo];
		pthread_mutex_lock(&philo->mtx_count_eat);
		if (philo->count_eat < table->must_eat_for_time)
			all_eat = FALSE;
		pthread_mutex_unlock(&philo->mtx_count_eat);
		if (!all_eat)
			break ;
		count_philo++;
	}
	if (all_eat)
		set_simulation_status(table, FALSE);
	return (all_eat);
}

/**
 * The monitor's thread method. This method will run until any philosopher
 * thread dies or everyone has eaten enough.
 *
 * @arg: a pointer to table struct
 *
*/
void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->must_eat_for_time == -1)
	{
		while (all_philo_alive(table))
			usleep(10);
	}
	else
	{
		while (all_philo_alive(table) && !all_philo_eating(table))
			usleep(10);
	}
	return (NULL);
}
