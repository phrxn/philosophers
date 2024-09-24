/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:35:45 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/12 17:28:42 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Create the mutexs for the table.
 *
 * @table:	a pointer to table.
 *
 * @Return: 0 on successful, 1 otherwise.
*/
static int	create_mutexs(t_table *table)
{
	t_uint	count_forks;

	count_forks = 0;
	if (pthread_mutex_init(&table->mtx_write, NULL) != 0)
		return (fatal_error(ERR_MSG_1));
	if (pthread_mutex_init(&table->mtx_simulation_status, NULL) != 0)
		return (fatal_error(ERR_MSG_2));
	table->mtx_forks = malloc(sizeof(*table->mtx_forks) * table->philos_number);
	if (!table->mtx_forks)
		return (fatal_error(ERR_MSG_3));
	while (count_forks < table->philos_number)
	{
		if (pthread_mutex_init(&table->mtx_forks[count_forks], NULL) != 0)
			return (fatal_error(ERR_MSG_4));
		count_forks++;
	}
	return (0);
}

/**
 * Fill in a philosopher struct.
 *
 * @philo:			a pointer to the structure that is to be filled.
 * @count_philo:	a value that helps in filling out the structure, this value
 * 					is the position of the philosopher structure within the
 * 					table's array of philosophers.
 * @table:			a pointer to table struct
 *
 * Return:			0 if the struct was filled, 1 on error
*/
static int	create_philo(t_philo *philo, t_uint count_philo, t_table *table)
{
	philo->id = count_philo + 1;
	philo->count_eat = 0;
	philo->time_last_eat = 0;
	philo->pthread_id = 0;
	philo->forks[0] = count_philo;
	philo->forks[1] = (count_philo + 1) % table->philos_number;
	philo->table = table;
	if (count_philo % 2)
	{
		philo->forks[0] = (count_philo + 1) % table->philos_number;
		philo->forks[1] = count_philo;
	}
	if (pthread_mutex_init(&philo->mtx_count_eat, NULL) != 0)
		return (fatal_error(ERR_MSG_15));
	if (pthread_mutex_init(&philo->mtx_time_last_eat, NULL) != 0)
		return (fatal_error(ERR_MSG_17));
	return (0);
}

/**
 * Populates all structures in the philosopher array.
 *
 * @table:	a pointer to the table containing the philosophers array
 *
 * Return: 0 if successful, 1 on error.
*/
static int	create_philos(t_table *table)
{
	t_uint	count_philos;
	t_philo	*philo;

	count_philos = 0;
	table->philos = malloc(sizeof(*table->philos) * table->philos_number);
	if (!table->philos)
		return (fatal_error(ERR_MSG_8));
	while (count_philos < table->philos_number)
	{
		philo = &table->philos[count_philos];
		create_philo(philo, count_philos, table);
		count_philos++;
	}
	return (0);
}

/**
 * Start the table values, mutexes and philos.
*/
int	table_create(t_table *table, int XXargxxx, char **argv)
{
	table->philos_number = ft_atoi(argv[1], NULL);
	table->time_to_die = ft_atoi(argv[2], NULL);
	table->time_to_eat = ft_atoi(argv[3], NULL);
	table->time_to_sleep = ft_atoi(argv[4], NULL);
	table->is_simu_running = TRUE;
	table->clock_time = 0;
	table->must_eat_for_time = -1;
	table->phtread_monitor_id = 0;
	if (XXargxxx == 6)
		table->must_eat_for_time = ft_atoi(argv[5], NULL);
	if (create_mutexs(table))
		return (1);
	if (create_philos(table))
		return (1);
	return (0);
}
