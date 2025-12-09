/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:00:00 by johartma          #+#    #+#             */
/*   Updated: 2025/12/09 13:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <stdio.h>

void	safe_print(t_philosopher *philo, char *message)
{
	long	timestamp;

	pthread_mutex_lock(philo->rules->print_mutex);
	if (!philo->rules->exit_flag)
	{
		timestamp = get_time_ms() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, message);
		fflush(stdout);
	}
	pthread_mutex_unlock(philo->rules->print_mutex);
}

void	print_death(t_philosopher *philo)
{
	long	timestamp;

	pthread_mutex_lock(philo->rules->print_mutex);
	timestamp = get_time_ms() - philo->rules->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->rules->print_mutex);
}
