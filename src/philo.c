/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/31 23:56:02 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* routine_monitor(void *args)
{}

void* routine(void *args)
{
	t_philo *philo;
	int i; 
	i =0;
	philo = (t_philo*)args;
	while (checking_for_cond(philo))
	{
		//for each thread i have 4 condition
		//1 .think btw the think time is the time we waiting for forks to be available 
		thinking(philo);//its just print its waiting and the actually waiting is in take forks fun
		//2 .take forks
		take_forks(philo);//now he can eat bc he have 2 forks
		//3 .eating
		eating(philo);
		ft_usleep(philo->rules_to_read_from->time_to_eat);
		//4 .put the forks
		release_forks(philo);
		//5 . sleeping after eating
		print_state(philo , GRAY , "is sleeping");
		ft_usleep(philo->rules_to_read_from->time_to_sleep);
		//we continue the loop
	}
	return NULL;
}

t_bool start_simulation(t_philo **philos , t_fork **forks , t_rules *rules)
{
	int i;

	i = 0;
	rules->end_simulation = FALSE;//FALSE -> the sim dose'nt end TRUE -> the sim is ended and no print is available for all thread
	pthread_mutex_init(&rules->mutex_end , NULL);
	// and the only one who can change is one thread the waiter (monitor) to make true
	rules->start_simulation = gettime_as_ms();//here the timer start
	while (i < rules->number_of_philos)
	{
		(*forks)->fork_id = i+1;
		pthread_create(&(*philos)[i].thread , NULL, &routine ,(philos)[i]);
		i++;
	}
	return TRUE;
}

int	main(int argc, char *argv[])
{
	t_rules	rules;
	t_philo *philos;
	t_fork *forks;

	philos = NULL;
	forks = NULL;
	rules.error = 2; // here the error if anything goes wrong
	if (!check_input(argc, argv, &rules))
		error_exit("error in the input",&rules,&forks,&philos);//here i make sure that in the begging to set philos and fork to null and error to 1
	if (!init_all(&philos , &forks , &rules))
		error_exit("error with init all fun" , &rules , &forks , &philos);
	printf("all input are good \n");//remove it later
	start_simulation(&philos , &forks , &rules);
	destroy_and_free_all(&forks , &philos , &rules);
}
