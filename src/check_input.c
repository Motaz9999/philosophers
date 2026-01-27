/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:37:04 by moodeh            #+#    #+#             */
/*   Updated: 2026/01/27 18:26:15 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_isdigit(int dig)
{
	if (dig >= '0' && dig <= '9')
		return (true);
	return (false);
}
static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (10 * result) + (*str - '0');
		str++;
	}
	return (result * sign);
}

static t_bool	check_for_str(char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
static t_bool	check_for_type(char **argv)
{
	char	**str;
	int		i;

	i = 1;
	str = argv;
	while (str[i] != NULL)
	{
		if (!check_for_str(str[i]))
			return (false); // ok here we check all the inputs
		i++;
	}
	return (true);
}
// here we check on args and save it to use later
t_bool	check_input(int argc, char *argv[], t_args *philo)
{
	if (!(argc == 5 || argc == 6))
		return (false);               // end the program
	memset(philo, 0, sizeof(t_args)); // here we make all the vars into 0
	if (!check_for_type(argv))        // here we check of all the strs are nums
		return (false);
	philo->number_of_philos = ft_atol(argv[1]);
	// here we make them long to be sure all nums are int
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		philo->number_of_times_to_eat = ft_atol(argv[5]);
	if (philo->number_of_philos > MAX_PHILOS || philo->number_of_philos < 1
		|| philo->time_to_die <= 0 || philo->time_to_die > INT_MAX
		|| philo->time_to_eat > INT_MAX || philo->time_to_eat <= 0
		|| philo->time_to_sleep > INT_MAX || philo->time_to_sleep <= 0
		|| ((argc == 6) && (philo->number_of_times_to_eat <= 0
				|| philo->number_of_times_to_eat > INT_MAX)))
		return (false);
	return (true); // all inputs are valid
}
