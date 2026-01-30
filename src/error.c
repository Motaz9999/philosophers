/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:10:14 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/30 20:27:46 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *msg, t_rules *rules, t_fork **forks, t_philo **philos)
{
	printf("Error: %s\n", msg);
	if (forks != NULL && *forks != NULL)
		destroy_forks(forks, rules->number_of_philos);

	if (philos != NULL && *philos != NULL)
		destroy_philos(philos, rules->number_of_philos);
	exit(rules->error);
		// if there is no error it should exit with code  0 and this is normal
}
