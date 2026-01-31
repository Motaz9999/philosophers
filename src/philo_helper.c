/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:14:49 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/31 23:52:16 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	print_state(t_philo *p, char *color, char *msg)
{
	pthread_mutex_lock(&p->rules_to_read_from->mutexPrint);
	if (!p->rules_to_read_from->end_simulation)
		printf("%s%ld %d %s%s\n", color, get_time()
			- p->rules_to_read_from->start_simulation, p->id, msg, RESET);
	pthread_mutex_unlock(&p->rules_to_read_from->mutexPrint);
}
void	thinking(t_philo *philo)
{
	print_state(philo, YELLOW, "is thinking");
}
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)//odd and even bc i dont want deadlock (even)
	{
		pthread_mutex_lock(philo->left_fork);//here we start with left
	    print_state(philo, CYAN, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
	    print_state(philo, CYAN, "has taken right right");
	}
	else //odd
	{
		pthread_mutex_lock(philo->right_fork);//another thread start with right 
	    print_state(philo, CYAN, "has taken right right");
		pthread_mutex_lock(philo->left_fork);
	    print_state(philo, CYAN, "has taken left fork");
	}
}
void eating(t_philo *philo)
{
    philo->num_of_meals_have_eaten++;
    philo->time_of_start_of_last_meal = gettime_as_ms();
    print_state(philo , GREEN , "is eating");
}

//must unlock them in reverse soo its always the same way (must not have deadlock)
void release_forks(t_philo *philo)
{
    if (!(philo->id % 2 == 0))//odd
	{
		pthread_mutex_unlock(philo->left_fork);
//	    print_state(philo, BLUE, "has release left fork");//this print is not s part of the subject 
		pthread_mutex_unlock(philo->right_fork);
//	    print_state(philo, BLUE, "has release right right");
	}
	else//even
	{
		pthread_mutex_unlock(philo->right_fork);
//	    print_state(philo, BLUE, "has release right right");
		pthread_mutex_unlock(philo->left_fork);
//	    print_state(philo, BLUE, "has release left fork");
	}
}

