/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmanoel- <dmanoel-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:37:52 by phz               #+#    #+#             */
/*   Updated: 2023/12/12 16:08:49 by dmanoel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERR_MSG_USAGE "usage : ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"

# define ERR_MSG_1 "phtread: error starting mutex write"
# define ERR_MSG_2 "phtread: error starting mutex simulation status"
# define ERR_MSG_3 "malloc: error when trying to allocate memory for forks"
# define ERR_MSG_4 "pthread: error starting the forks mutex"

# define ERR_MSG_5 "pthread: error ending mutex write"
# define ERR_MSG_6 "pthread: error ending mutex simulation status"
# define ERR_MSG_7 "pthread: error ending the forks mutex"

# define ERR_MSG_8 "malloc: error when trying to allocate memory for philos"

# define ERR_MSG_9 "pthread: error starting mutex philo dead"
# define ERR_MSG_10 "pthread: error ending mutex philo dead"
# define ERR_MSG_11 "pthread: error to create philos pthread"
# define ERR_MSG_12 "pthread: error to join philo pthread"
# define ERR_MSG_13 "pthread: error to create monitor pthread"
# define ERR_MSG_14 "pthread: error to join monitor pthread"

# define ERR_MSG_15 "pthread: error starting mutex philo count eat"
# define ERR_MSG_16 "pthread: error ending mutex philo count eat"
# define ERR_MSG_17 "pthread: error starting mutex philo time last eat"
# define ERR_MSG_18 "pthread: error ending mutex philo time last eat"

# define FALSE ((char)0)
# define TRUE ((char)1)

# define INT_MAX 2147483647

typedef struct s_philo	t_philo;

typedef unsigned int	t_uint;

typedef struct s_table
{
	t_uint			philos_number;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_think;
	time_t			clock_time;
	int				must_eat_for_time;
	char			is_simu_running;
	pthread_mutex_t	mtx_simulation_status;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_write;
	t_philo			*philos;
	pthread_t		phtread_monitor_id;
}	t_table;

typedef struct s_philo
{
	t_uint			id;
	pthread_t		pthread_id;
	int				count_eat;
	pthread_mutex_t	mtx_count_eat;
	t_uint			forks[2];
	time_t			time_last_eat;
	pthread_mutex_t	mtx_time_last_eat;
	t_table			*table;

}	t_philo;

typedef enum e_status
{
	TAKE_FORK = 1,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_status;

// ----------- args.c -----------
int		is_input_valid(int XXargxxx, char **argv);

// ----------- check_parameters.c -----------
int		all_parameters_numbers(char **number_list);

// ----------- convert.c -----------
int		ft_atoi(const char *number, int *status);

// ----------- message.c -----------
int		fatal_error(char *msg);

// ----------- table.c -----------
int		table_create(t_table *table, int XXargxxx, char **argv);

// ----------- table2.c -----------
void	table_destroy(t_table *table);

// ----------- simulation.c -----------
int		is_simulation_running(t_table *table);
void	set_simulation_status(t_table *table, int status);

// ----------- message.c -----------
void	printf_philo(t_philo *philo, time_t time, t_status status,
			int is_monit);

// ----------- monitor.c -----------
void	*monitor(void *arg);

// ----------- philosopher.c -----------
void	*routine(void *arg);

// ----------- philosopher2.c -----------
void	*alone(t_philo *philo);

// ----------- time.c -----------
time_t	get_time_ms(void);
void	sleep_in_ms(t_table *table, time_t milli);

#endif
