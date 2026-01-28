/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:06:57 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/28 23:31:21 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
//# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0
# define MAX_PHILOS 200

typedef int	t_bool;

typedef struct s_rules
{
	long number_of_philos; // The number of philosophers and also the number of forks
	long time_to_die; // If a philosopher has not started eating within time_to_die milliseconds since the start of their last meal or the start of the simulation, they die
	long time_to_eat; // The time it takes for a philosopher to eat. During that time, they will need to hold two forks
	long time_to_sleep; // The time a philosopher will spend sleeping
	long number_of_times_to_eat;// If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies
	long start_simulation;//here is the time i start to give it to all philos
	long end_simiulation;// when a one philo dies //or all philos have eat all there meals 
 }			t_rules;// ok these rules is for all philos its the same for all 
//here we check the input
typedef struct s_philo
{
	int id;//this the name of philo
	int num_of_meals_have_eaten;//if the phlio eat all the meals (the thread end)
	pthread_t thread;//here is where i start the thread
	
}	t_philo;

t_bool	check_input(int argc, char *argv[], t_rules *philo);

#endif