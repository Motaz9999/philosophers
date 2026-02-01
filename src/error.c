/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:10:14 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 01:41:44 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *msg, t_rules *rules, t_fork **forks, t_philo **philos)
{
	int	i;

	while (philos[i]->thread != 0)
		i++;
	printf("Error: %s\n", msg);
	if (philos != NULL && *philos != NULL)
		destroy_philos(philos, i);
	if (forks != NULL && *forks != NULL)
		destroy_forks(forks, rules->number_of_philos);
	exit(rules->error);
}
