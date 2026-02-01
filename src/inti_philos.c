/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:31:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 00:39:24 by moodeh           ###   ########.fr       */
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
		if (pthread_mutex_init(&(*forks)[i].mutex_fork, NULL) != 0)
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
		(*philos)[i].meals_eat = 0;
		(*philos)[i].time_of_meal = 0;//change it later when start the sim
		(*philos)[i].thread = 0;
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % rules->number_of_philos];//which fork i have pointer to it 
		//now the mutexes
		if (pthread_mutex_init(&(*philos)[i].mutex_meal , NULL) != 0)
		{
			destroy_forks(forks , rules->number_of_philos);
			destroy_philos(philos , i);
		}
		i++;
	}
	return (TRUE);
}

t_bool init_mutex(t_rules *rules , t_fork **forks)
{
	rules->error = 2;
	if (pthread_mutex_init(&rules->mutex_end , NULL) != 0)
	{
		destroy_forks(forks ,rules->number_of_philos);
		destroy_philos(&rules->philos , rules->number_of_philos);
		return FALSE;
	}
	if (pthread_mutex_init(&rules->mutex_print , NULL))
	{
		destroy_forks(forks ,rules->number_of_philos);
		destroy_philos(&rules->philos , rules->number_of_philos);
		pthread_mutex_destroy(&rules->mutex_end);
		return FALSE;
	}
	rules->error = 0;
	return TRUE;
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
	memset(*philos, 0 , sizeof(t_philo)*rules->number_of_philos);//memset the whole array
	memset(*forks , 0 , sizeof(t_fork)*rules->number_of_philos);
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
	rules->philos = *philos;//pointer to the whole array
	return (init_mutex(rules , forks));
}
