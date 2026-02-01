/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:14:49 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 00:31:25 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_state(t_philo *p, char *color, char *msg)
{
	pthread_mutex_lock(&p->rules_to_read_from->mutex_print);
	if (!p->rules_to_read_from->end_simulation)
		printf("%s%ld %d %s%s\n", color, gettime_as_ms()
			- p->rules_to_read_from->start_simulation, p->id, msg, RESET);
	pthread_mutex_unlock(&p->rules_to_read_from->mutex_print);
}
void	thinking(t_philo *philo)
{
	print_state(philo, YELLOW, "is thinking");
}
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
	    print_state(philo, CYAN, "has taken  fork");
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
	    print_state(philo, CYAN, "has taken  fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
	    print_state(philo, CYAN, "has taken fork");
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
	    print_state(philo, CYAN, "has taken fork");
	}
}
void eating(t_philo *philo)
{//add mutex here
    philo->meals_eat++;
    philo->time_of_meal = gettime_as_ms();
    print_state(philo , GREEN , "is eating");
}

//must unlock them in reverse soo its always the same way (must not have deadlock)
void release_forks(t_philo *philo)
{
    if (!(philo->id % 2 == 0))
	{
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	}
	else//even
	{
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	}
}

