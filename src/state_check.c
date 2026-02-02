/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 03:49:23 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/02 05:31:24 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this fun see if the fun is dead by checking on his state
// now - last_time == time_to_die ?
t_bool	check_philo_death(t_philo *philo)
{
	long	time_now;
	t_bool	is_dead;

	is_dead = FALSE; // here this mean that the philo isnt dead
	pthread_mutex_lock(&philo->mutex_meal);
	time_now = gettime_as_ms();
	if ((time_now
			- philo->time_of_meal) >= philo->rules_to_read_from->time_to_die)
		is_dead = TRUE; // now it is dead
	pthread_mutex_unlock(&philo->mutex_meal);
	return (is_dead);
}

// this fun for the threads to check
t_bool	is_simulation_stopped(t_rules *rules)
{
	t_bool	is_end;

	pthread_mutex_lock(&rules->mutex_end);
	is_end = rules->end_simulation;
	pthread_mutex_unlock(&rules->mutex_end);
	return (is_end);
}
// here we check on all philos if they eat all there meals
t_bool	all_philos_full(t_rules *rules)
{
	int		i;
	t_bool	all_full;
	long	meals;

	all_full = TRUE; // all are full
	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_mutex_lock(&rules->philos[i].mutex_meal);
		meals = rules->philos[i].meals_eat;
		pthread_mutex_unlock(&rules->philos[i].mutex_meal);
		if (meals < rules->number_of_times_to_eat)
		{
			all_full = FALSE; // some one didnt eat all his meals
			break ;
		}
		i++;
	}
	return (all_full);
}
// here we set the flage to an end
void	set_death_flag(t_rules *rules, int flag)
{
	pthread_mutex_lock(&rules->mutex_end);
	rules->end_simulation = flag;
	pthread_mutex_unlock(&rules->mutex_end);
}

void	print_death(t_philo *p)
{
	pthread_mutex_lock(&p->rules_to_read_from->mutex_print);    
	printf("%s%ld %d %s%s\n", RED, gettime_as_ms()
		- p->rules_to_read_from->start_simulation, p->id, "is dead", RESET);
	pthread_mutex_unlock(&p->rules_to_read_from->mutex_print);
}