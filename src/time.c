/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:19:05 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/28 23:30:40 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//the tv have 2 vars first is the tv_sec that is the normal sec
//and the sec var is tv_usec that is the micro sec that comes with sec
//so i must make both in the same type (ms) and sum them
//and now i have the whole number as ms
long gettime_as_ms(void)
{
    struct timeval tv;//this time variable that can access the next fun 
    gettimeofday(&tv , NULL);// now the tv have value as sec and i want it as milisec
    return (tv.tv_sec * 1000 + tv.tv_sec/1000);
}
