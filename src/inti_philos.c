/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 03:31:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/29 05:05:57 by moodeh           ###   ########.fr       */
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
		forks[i]->fork_id = i;
		if (pthread_mutex_init(forks[i]->fork_id, NULL) != 0)
			return ();//if the init fall i should destroy anything remain non desrtroyed
		// here we make fun to destroy forks until there is nothing left
		i++;
	}
	return (TRUE);
}
t_bool	fill_philos(t_philo **philos, t_fork **forks, long num_of_philos)
{
	return (TRUE);
}
t_bool	init_all(t_philo **philos, t_fork **forks, t_rules *rules)
{
	// first inti philos and make them on the heap
	*philos = malloc(sizeof(t_philo) * rules->number_of_philos + 1);
	// here we make the array and the last element is null
	if (*philos == NULL)
		return (FALSE);
	*forks = malloc(sizeof(t_fork) * rules->number_of_philos + 1);
	if (*forks == NULL)
	{
		free(*philos);
		return (FALSE);
	}
	// now after i malloc the array i  i must fill the array of forks first then
	if (!fill_forks(forks, rules->number_of_philos) || !fill_philos(philos,
			forks, rules->number_of_philos))
		return (FALSE);//here we have the malloc for the array dont forgot to free it
	return (TRUE);
}
