/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:19:05 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/01 23:48:07 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// so here i can take time as ms without convert it
// how much time u want to spend
long	ft_usleep(long ms_time)
{
	long	start;

	start = gettime_as_ms(); // the now time i want to reach as the input number
	while ((gettime_as_ms() - start) < ms_time)
		usleep(500);
			// each one is .5++ ms till it goes to reach the ms_time half by half (this is the accurate way)
	return (0);
}
// the tv have 2 vars first is the tv_sec that is the normal sec
// and the sec var is tv_usec that is the micro sec that comes with sec
// so i must make both in the same type (ms) and sum them
// and now i have the whole number as ms
long	gettime_as_ms(void)
{
	struct timeval tv;       // this time variable that can access the next fun
	gettimeofday(&tv, NULL);
		// now the tv have value as sec and i want it as millisec
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
