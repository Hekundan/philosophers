/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:37:44 by johartma          #+#    #+#             */
/*   Updated: 2025/05/26 17:33:14 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../philosophers.h"
#include <pthread.h>
#include <stdlib.h>

int	init_mutex(pthread_mutex_t *forks, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			ft_putstr_fd("Mutex init failed", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_threads(t_philosopher *philosopher)
{
	int	i;
	int	n_threads;

	n_threads = philosopher->rules->n_philos;
	i = 0;
	while (i < n_threads)
	{
		if (pthread_create(&(philosopher[i].thread),
				NULL, philo_routine, &(philosopher[i])))
		{
			ft_putstr_fd("Thread creation failed", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_rules_mutexes(t_rules *rules)
{
	rules->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!rules->print_mutex)
		return (-1);
	if (pthread_mutex_init(rules->print_mutex, NULL))
	{
		free(rules->print_mutex);
		return (-1);
	}
	rules->philosphers_finished_eating = malloc(sizeof(int));
	if (!rules->philosphers_finished_eating)
	{
		pthread_mutex_destroy(rules->print_mutex);
		free(rules->print_mutex);
		return (-1);
	}
	*rules->philosphers_finished_eating = 0;
	rules->exit_flag = false;
	rules->start_time = get_time_ms();
	return (0);
}
