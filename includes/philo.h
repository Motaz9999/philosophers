/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:06:57 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/04 23:46:28 by moodeh           ###   ########.fr       */
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
# include "colors.h"
# define TRUE 1
# define FALSE 0

typedef int	t_bool;
typedef struct s_rules t_rules;
typedef struct s_philo t_philo;

typedef struct s_fork
{
	int fork_id;
	pthread_mutex_t mutex_fork;
} t_fork; 

typedef struct s_rules
{
	long number_of_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int error;
	long number_of_times_to_eat;
	long start_simulation;
	t_bool end_simulation;//here we decide if we want to end the program
	pthread_mutex_t mutex_end;
	pthread_mutex_t mutex_print;
	t_philo *philos;//i save the philos here if i want to see them
 }			t_rules;
 
typedef struct s_philo
{
	int id;
	int meals_eat;
	long time_of_meal;
	pthread_mutex_t mutex_meal;
	pthread_t thread;
	t_fork *right_fork;
	t_fork *left_fork;
	t_rules *rules_to_read_from;
}	t_philo;

//check funs	
t_bool	check_input(int argc, char *argv[], t_rules *philo);
//time funs
long gettime_as_ms(void);
long ft_usleep(long ms_time);
//main funs

//error handle for now 
void	error_exit(char *msg, t_rules *rules, t_fork **forks, t_philo **philos);
//initialization
t_bool	fill_forks(t_fork **forks, long num_of_forks);
t_bool	fill_philos(t_philo **philos, t_fork **forks, t_rules *rules);
t_bool	init_all(t_philo **philos, t_fork **forks, t_rules *rules);
//destroy
void	destroy_forks(t_fork **forks, long len_of_arrs);
void	destroy_philos(t_philo **philos, long len_of_arrs);
void	destroy_and_free_all(t_fork **forks, t_philo **philos, t_rules *rules);
//helper
void release_forks(t_philo *philo);
void eating(t_philo *philo);
void	take_forks(t_philo *philo);
void	thinking(t_philo *philo);
void	print_state(t_philo *p, char *color, char *msg);
//state checking
t_bool	check_philo_death(t_philo *philo);
t_bool	is_simulation_stopped(t_rules *rules);
t_bool	all_philos_full(t_rules *rules);
void	set_death_flag(t_rules *rules, int flag);
void print_death(t_philo *philo);
#endif