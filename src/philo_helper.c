/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:14:49 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 21:13:53 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *p, char *color, char *msg)
{
	pthread_mutex_lock(&p->rules_to_read_from->mutex_print);
	pthread_mutex_lock(&p->rules_to_read_from->mutex_end);
	if (!p->rules_to_read_from->end_simulation)
	{
		printf("%s%ld %d %s%s\n", color, gettime_as_ms()
			- p->rules_to_read_from->start_simulation, p->id, msg, RESET);
	}
	pthread_mutex_unlock(&p->rules_to_read_from->mutex_end);
	pthread_mutex_unlock(&p->rules_to_read_from->mutex_print);
}
void	thinking(t_philo *philo)
{
	t_rules	*r;
	long	t_to_eat;
	long	t_to_sleep;
	long	think_time;

	r = philo->rules_to_read_from;
	print_state(philo, YELLOW, "is thinking");
	// If N is even, they don't really need to think.
	// If N is odd, we calculate a safe think time.
	if (r->number_of_philos % 2 != 0)
	{
		t_to_eat = r->time_to_eat;
		t_to_sleep = r->time_to_sleep;
		think_time = t_to_eat * 2 - t_to_sleep;
		if (think_time < 0)
			think_time = 0;
		ft_usleep(think_time * 0.4);//the best to take from time is from 40-50% of his free time so in this percent he give a time to other to eat
	}
}
void	take_forks(t_philo *philo)
{
	if (philo->rules_to_read_from->number_of_philos == 1)
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		print_state(philo, CYAN, "has taken fork");
		ft_usleep(philo->rules_to_read_from->time_to_die);
			// i will kill it before it trt to take another fork
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		return ;
	}
	if (philo->id % 2 == 0) //this even  
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		print_state(philo, CYAN, "has taken fork");
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		print_state(philo, CYAN, "has taken fork");
	}
	else//1=> odd take first here i start first
	{
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		print_state(philo, CYAN, "has taken fork");
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		print_state(philo, CYAN, "has taken fork");
	}
}
void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->meals_eat++;
	philo->time_of_meal = gettime_as_ms(); // this like the time he will survive
	pthread_mutex_unlock(&philo->mutex_meal);
	print_state(philo, GREEN, "is eating");
	ft_usleep(philo->rules_to_read_from->time_to_eat);
}

// must unlock them in reverse soo its always the same way (must not have deadlock)
void	release_forks(t_philo *philo)
{
	if (philo->rules_to_read_from->number_of_philos == 1)
		return ;
	if (philo->id % 2 == 0)//even from right to left
	{
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	}
	else//from left to right 
	{
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	}
}
