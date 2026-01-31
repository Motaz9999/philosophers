/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/31 20:13:55 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* routine(void *args)
{
	t_philo *philo;
	int i; 
	i =0;
	philo = (t_philo*)args;
	//when the philo is dead or end the simulation
	while (TRUE)
	{
		
	}
		return NULL;
}

t_bool start_simulation(t_philo **philos , t_fork **forks , t_rules *rules)
{
	int i;

	i = 0;
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
