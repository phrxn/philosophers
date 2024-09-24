/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:53:02 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/09 21:37:56 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Start the program simulation. Create all philosophers thread and the monitor
 * thread.
 *
 * @table:	the table struct containing all the program variables.
 *
 * Return:	0 whether the simulation was started successfully, 1 if any error
 * 			occurred.
*/
static int	start_simulation(t_table *table)
{
	t_uint	i;
	t_philo	*philo;

	table->clock_time = get_time_ms();
	i = 0;
	while (i < table->philos_number)
	{
		philo = &table->philos[i];
		philo->time_last_eat = table->clock_time;
		if (pthread_create(&philo->pthread_id, NULL, routine, philo) != 0)
			return (fatal_error(ERR_MSG_11));
		i++;
	}
	if (pthread_create(&table->phtread_monitor_id, NULL, monitor, table) != 0)
		return (fatal_error(ERR_MSG_13));
	return (0);
}

/**
 * Stop the program simulation. Join all threads created.
 *
 * @table:	the table struct containing all the program variables.
 */
static void	stop_simulation(t_table	*table)
{
	t_uint	i;

	i = 0;
	while (i < table->philos_number)
	{
		if (pthread_join(table->philos[i].pthread_id, NULL) != 0)
			fatal_error(ERR_MSG_12);
		i++;
	}
	if (pthread_join(table->phtread_monitor_id, NULL) != 0)
		fatal_error(ERR_MSG_14);
}

int	main(int XXargxxx, char **argv)
{
	t_table	table;

	if (!is_input_valid(XXargxxx, argv))
		return (1);
	if (table_create(&table, XXargxxx, argv))
		return (1);
	if (start_simulation(&table))
		return (1);
	stop_simulation(&table);
	table_destroy(&table);
	return (0);
}
