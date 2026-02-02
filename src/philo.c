/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 21:05:01 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 20:33:20 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ok in this thread i want to check on other threads
// first loop is for the thread for goes forever or until he find another one
// 1. i need to check on the death of philos

void	*routine_monitor(void *args)
{
	int		i;
	t_rules	*rules;

	rules = (t_rules *)args;
	while (TRUE)
	{
		i = 0;
		while (i < rules->number_of_philos)
		{
			if (check_philo_death(&rules->philos[i]))
			{
				set_death_flag(rules, 1);
				print_death(&rules->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (rules->number_of_times_to_eat > 0 && all_philos_full(rules))
		{
			set_death_flag(rules, 1);
			return (NULL);
		}
		ft_usleep(1); // check every 1ms
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo	*philo;
	int meals;
	
	philo = (t_philo *)args;
	if (philo->id % 2 == 0)//even wait
		ft_usleep(philo->rules_to_read_from->time_to_eat / 2);
	while (!is_simulation_stopped(philo->rules_to_read_from))
	{
		if (philo->rules_to_read_from->number_of_times_to_eat > 0)
        {
            pthread_mutex_lock(&philo->mutex_meal);
            meals = philo->meals_eat;
            pthread_mutex_unlock(&philo->mutex_meal);
            if (meals >= philo->rules_to_read_from->number_of_times_to_eat)
                break;
        }
		take_forks(philo);
		eating(philo);
		release_forks(philo);
		print_state(philo, GRAY, "is sleeping");
		ft_usleep(philo->rules_to_read_from->time_to_sleep);
		thinking(philo);
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
				&(*philos)[i]) != 0)
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
		exit(rules.error);
	if (!init_all(&philos, &forks, &rules))
		exit(rules.error);
	start_simulation(&philos, &forks, &rules);
	destroy_and_free_all(&forks, &philos, &rules);
	exit(rules.error);
}
