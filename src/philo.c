/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/30 21:12:22 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void* routine(void)
{
	printf("create new thread\n");
	return NULL;
}

int	main(int argc, char *argv[])
{
	t_rules	rules;
	t_philo *philos;
	t_fork *forks;
//	int i;
	philos = NULL;
	forks = NULL;
//	i =0;
	if (!check_input(argc, argv, &rules))
		error_exit("error in the input",&rules,&forks,&philos);//here i make sure that in the begging to set philos and fork to null and error to 1
    printf("all input are good \n");//remove it later
	if (!init_all(&philos , &forks , &rules))
		error_exit("error with init all fun" , &rules , &forks , &philos);
	//now after init
	//add fun for all this stuff
    // rules.start_simulation = gettime_as_ms();//here the timer start
	// while (i < rules.number_of_philos)
	// {
	// 	pthread_create();
	// 	i++;
	// }
	// i = 0;
	// while (i < rules.number_of_philos)
	// {
	// 	if (pthread_join())
	// 	i++;
	// }
	printf("all is ok and init just right \n ");
	destroy_and_free_all(&forks , &philos , &rules);
	return 0;
}
