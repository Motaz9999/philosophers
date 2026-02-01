/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 02:05:28 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ok in this thread i want to check on other threads
//first loop is for the thread for goes forever or until he find another one
// 1. i need to check on the death of philos

void	*routine_monitor(void *args)
{
	int		i;
	t_rules	*rules;

	rules = (t_rules *)args;
	while (TRUE)
	{
		i = 0;
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		thinking(philo);
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		print_state(philo, GRAY, "is sleeping");
		ft_usleep(philo->rules_to_read_from->time_to_sleep);
	}
	return (NULL);
}

t_bool	start_simulation(t_philo **philos, t_fork **forks, t_rules *rules)
{
	int			i;
	long		start_time;
	pthread_t	thread;

	i = 0;
	start_time = gettime_as_ms();         // ok i have time as  ms
	rules->end_simulation = FALSE;        // we wouldn't end it
	rules->start_simulation = start_time; // ok now also i have time
	while (i < rules->number_of_philos)
	{
		pthread_mutex_lock(&(*philos)[i].mutex_meal);
		(*philos)[i].time_of_meal = start_time;
		(*philos)[i].meals_eat = 0;
		pthread_mutex_unlock(&(*philos)[i].mutex_meal);
		if (pthread_create(&(*philos)[i].thread, NULL, &routine,
				(philos)[i]) != 0)
			error_exit("error in create thread", rules, forks, philos);
		i++;
	}
	if (pthread_create(&thread, NULL, routine_monitor, rules) != 0)
		error_exit("error in create thread monitor", rules, forks, philos);
	pthread_join(thread, NULL);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;
	t_philo	*philos;
	t_fork	*forks;

	philos = NULL;
	forks = NULL;
	if (!check_input(argc, argv, &rules))
		error_exit("error in the input", &rules, &forks, &philos);
	// here i make sure that in the begging to set philos and fork to null and error to 1
	if (!init_all(&philos, &forks, &rules))
		error_exit("error with init all fun", &rules, &forks, &philos);
	printf("all input are good \n");
	start_simulation(&philos, &forks, &rules);
	destroy_and_free_all(&forks, &philos, &rules);
	exit(rules.error);
}
