/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:31:59 by dmanoel-          #+#    #+#             */
/*   Updated: 2023/12/13 13:20:13 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	sleep_in_ms(t_table *table, time_t milli)
{
	time_t	wait;

	wait = get_time_ms() + milli;
	while (get_time_ms() < wait && is_simulation_running(table))
	{
		usleep(100);
	}
}
