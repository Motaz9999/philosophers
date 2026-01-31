/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:31:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/31 18:59:54 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// init_all(philos , forks , &rules);
// ok here we make an arrays of structs on the heap
// btw the 2 star mean its a pointer soo its ok
t_bool	fill_forks(t_fork **forks, long num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		(*forks)[i].fork_id = i + 1;//this is the id of the forks so it has to be as the philos ids 
		if (pthread_mutex_init(&(*forks)[i].mutexFork, NULL) != 0)
		{
			destroy_forks(forks, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool	fill_philos(t_philo **philos, t_fork **forks, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		(*philos)[i].id = i + 1; // bc we start from 1 (id not array)
		(*philos)[i].rules_to_read_from = rules;
		(*philos)[i].num_of_meals_have_eaten = 0;
		(*philos)[i].time_of_start_of_last_meal = 0;
		(*philos)[i].thread = 0;
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % rules->number_of_philos];
		i++;
	}
	return (TRUE);
}

t_bool	init_all(t_philo **philos, t_fork **forks, t_rules *rules)
{
	*philos = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (*philos == NULL)
		return (FALSE);
	*forks = malloc(sizeof(t_fork) * rules->number_of_philos);
	if (*forks == NULL)
	{
		free(*philos);
		return (FALSE);
	}
	memset((*philos) , 0 , sizeof(t_philo));
	memset((*forks) , 0 , sizeof(t_fork));
	if (!fill_forks(forks, rules->number_of_philos))
	{
		free(*philos);
		free(*forks);
		return (FALSE);
	}
	if (!fill_philos(philos, forks, rules))
	{
		destroy_forks(forks, rules->number_of_philos);
		free(*philos);
		return (FALSE);
	}
	rules->error = 0; // all ok now
	return (TRUE);
}
