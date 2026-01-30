/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:31:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/30 19:14:12 by moodeh           ###   ########.fr       */
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
        (*forks)[i].fork_id = i;
		(*forks)[i].mutexFork = malloc(sizeof(pthread_mutex_t));//any struct i malloc in heap the elements inside in must be also mallcod
		if ((*forks)[i].mutexFork == NULL)
		{
			destroy_forks(forks , i);
			return FALSE;
		}
		if (pthread_mutex_init((*forks)[i].mutexFork, NULL) != 0)
		{
			free((*forks)[i].mutexFork);
			destroy_fork(forks, i);
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
		(*philos)[i].id = i +1;//bc we start from 1 (id not array)
		(*philos)[i].rules_to_read_from = i;
		(*philos)[i].rules_to_read_from = rules;
		(*philos)[i].num_of_meals_have_eaten =0;
		(*philos)[i].thread = NULL;
		(*philos)[i].left_fork = &(*forks)[i];
        (*philos)[i].right_fork = &(*forks)[(i + 1) % rules->number_of_philos];
		i++;
	}
	return (TRUE);
}
t_bool	init_all(t_philo **philos, t_fork **forks, t_rules *rules)
{
	rules->error = 2;//here the error if anything goes wrong
	*philos = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (*philos == NULL)
		return (FALSE);
	*forks = malloc(sizeof(t_fork) * rules->number_of_philos);
	if (*forks == NULL)
	{
		free(*philos);
		return (FALSE);
	}
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
	rules->error = 0;//all ok now
	return (TRUE);
}
