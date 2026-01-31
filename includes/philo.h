/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:06:57 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/31 20:26:25 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h>
# include <string.h>
# define TRUE 1
# define FALSE 0
# define MAX_PHILOS 200

typedef int	t_bool;

typedef struct s_fork
{
	int fork_id;//any fork must have an id
	pthread_mutex_t mutexFork;//for each fork must have it own mutex so that one thread can access it
} t_fork;//here is the forks that any thread can access it 

typedef struct s_rules
{
	long number_of_philos; // The number of philosophers and also the number of forks
	long time_to_die; // If a philosopher has not started eating within time_to_die milliseconds since the start of their last meal or the start of the simulation, they die
	long time_to_eat; // The time it takes for a philosopher to eat. During that time, they will need to hold two forks
	long time_to_sleep; // The time a philosopher will spend sleeping
	long number_of_times_to_eat;// If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies
	long start_simulation;//here is the time i start to give it to all philos
	long end_simulation;// when a one philo dies //or all philos have eat all there meals
	int error;//here i store error as exit code soo if i find any error i save here until i exit the program
	pthread_mutex_t mutexPrint;//soo i can use printf inside each philos and there is no data trace 
 }			t_rules;// ok these rules is for all philos its the same for all 
//here we check the input
typedef struct s_philo
{
	int id;//this the name of philo
	int num_of_meals_have_eaten;//if the philo eat all the meals (the thread end)
	long time_of_start_of_last_meal;//it have the time of the last meal (start of it)
	pthread_t thread;//here is where i start the thread
	t_fork *right_fork; // each philo when he trying to eat must have right and left fork 
	t_fork *left_fork;
	t_rules *rules_to_read_from;//here i can access the the whole rules
}	t_philo;//the philos as thread and have it own data

//check funs	
t_bool	check_input(int argc, char *argv[], t_rules *philo);
//time funs
long gettime_as_ms(void);
long ft_usleep(long ms_time);
//main funs

//error handle for now 
void	error_exit(char *msg , t_rules *rules , t_fork **forks , t_philo **philos);
//initialization
t_bool	fill_forks(t_fork **forks, long num_of_forks);
t_bool	fill_philos(t_philo **philos, t_fork **forks, t_rules *rules);
t_bool	init_all(t_philo **philos, t_fork **forks, t_rules *rules);
//destroy
void	destroy_forks(t_fork **forks, long len_of_arrs);
void	destroy_philos(t_philo **philos, long len_of_arrs);
void	destroy_and_free_all(t_fork **forks, t_philo **philos, t_rules *rules);

#endif