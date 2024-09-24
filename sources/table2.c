/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 23:06:52 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/09 18:45:48 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_mutexs(t_table *table)
{
	t_uint	count_forks;

	count_forks = 0;
	if (pthread_mutex_destroy(&table->mtx_write) != 0)
		return (fatal_error(ERR_MSG_5));
	if (pthread_mutex_destroy(&table->mtx_simulation_status) != 0)
		return (fatal_error(ERR_MSG_6));
	while (count_forks < table->philos_number)
	{
		if (pthread_mutex_destroy(&table->mtx_forks[count_forks]) != 0)
			return (fatal_error(ERR_MSG_7));
		count_forks++;
	}
	if (table->mtx_forks)
		free(table->mtx_forks);
	return (0);
}

static void	destroy_philos(t_table *table)
{
	t_uint	count_philos;
	t_philo	*philo;

	count_philos = 0;
	while (count_philos < table->philos_number)
	{
		philo = &table->philos[count_philos];
		if (pthread_mutex_destroy(&philo->mtx_count_eat) != 0)
			fatal_error(ERR_MSG_16);
		if (pthread_mutex_destroy(&philo->mtx_time_last_eat) != 0)
			fatal_error(ERR_MSG_18);
		count_philos++;
	}
	if (table->philos)
		free(table->philos);
}

void	table_destroy(t_table *table)
{
	destroy_mutexs(table);
	destroy_philos(table);
}
