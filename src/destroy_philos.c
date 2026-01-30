/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:44:40 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/30 20:27:01 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_fork **forks, long len_of_arrs)
{
	int	i;

	i = 0;
	if ((*forks) == NULL)
		return ;
	while (i < len_of_arrs)
	{
		if ((*forks)[i].mutexFork != NULL)
		{
			pthread_mutex_destroy((*forks)[i].mutexFork);
			free((*forks)[i].mutexFork);
		}
		i++;
	}
	free(*forks);
	*forks = NULL;
}

void	destroy_philos(t_philo **philos, long len_of_arrs)
{
	int	i;

	if (*philos == NULL)
		return ;
	while (i < len_of_arrs)
	{
		if ((*philos)[i].thread != 0)
			pthread_join((*philos)[i].thread, NULL);
		i++;
	}
    free(*philos);
    *philos = NULL;
}

void	destroy_and_free_all(t_fork **forks, t_philo **philos, t_rules *rules)
// 0 on no error else there are
{
	destroy_forks(forks, rules);
	destroy_philos(philos, rules);
	exit(rules->error);
}
