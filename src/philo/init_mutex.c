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
			ft_putstr_fd("Mutex init failed", 1);
			return (-1);
		}
		i++;
	}
}
