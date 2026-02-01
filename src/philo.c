/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 01:04:44 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* routine_montior(void *args)
{}
void* routine(void *args)
{
	t_philo *philo;

	philo = (t_philo*)args;
	while (1)
	{

		thinking(philo);

		take_forks(philo);
		eating(philo);
		ft_usleep(philo->rules_to_read_from->time_to_eat);
		release_forks(philo);
		print_state(philo , GRAY , "is sleeping");
		ft_usleep(philo->rules_to_read_from->time_to_sleep);
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
	if (!check_input(argc, argv, &rules))
		error_exit("error in the input",&rules,&forks,&philos);//here i make sure that in the begging to set philos and fork to null and error to 1
	if (!init_all(&philos , &forks , &rules))
		error_exit("error with init all fun" , &rules , &forks , &philos);
	
	printf("all input are good \n");
//	start_simulation(&philos , &forks , &rules);
	destroy_and_free_all(&forks , &philos , &rules);
}
