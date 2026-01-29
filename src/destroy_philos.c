/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:44:40 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/29 05:06:27 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_bool destroy_philos(t_philo **philos ,long len_of_arrs)
{
    
}

t_bool destroy_and_free(t_fork **forks , t_philo **philos , long len_of_arrs)
{
    
}

void destroy_forks(t_fork **forks ,long len_of_arrs )
{
    int i;
    i = 0;
    if (*forks == NULL)
        return ;
    while (i < len_of_arrs)
    {
        
    }
    free(forks);
    return TRUE;
}