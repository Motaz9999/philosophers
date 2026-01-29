/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/29 04:16:19 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* routine(void *arg)
{
	printf("create new thread\n");
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_rules	rules;
	t_philo *philos;//array of philos in heap 
	t_fork *forks;//array of forks in heap
	int i;
	i =0;
	if (!check_input(argc, argv, &rules))
		return (FALSE);
    printf("all input are good \n");//remove it later
	if (!init_all(&philos , &forks , &rules))
		return FALSE;



	
    rules.start_simulation = gettime_as_ms();//here the timer start
	while (i < rules.number_of_philos)
	{
		pthread_create();
		i++;
	}
	i = 0;
	while (i < rules.number_of_philos)
	{
		if (pthread_join())
		i++;
	}
	destroy_all();
	return 0;
}
