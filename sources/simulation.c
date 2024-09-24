/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:24:30 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/09 17:57:38 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_running(t_table *table)
{
	int	status;

	status = FALSE;
	pthread_mutex_lock(&table->mtx_simulation_status);
	if (table->is_simu_running)
		status = TRUE;
	pthread_mutex_unlock(&table->mtx_simulation_status);
	return (status);
}

void	set_simulation_status(t_table *table, int status)
{
	pthread_mutex_lock(&table->mtx_simulation_status);
	table->is_simu_running = status;
	pthread_mutex_unlock(&table->mtx_simulation_status);
}
