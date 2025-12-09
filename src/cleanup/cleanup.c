/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:00:00 by johartma          #+#    #+#             */
/*   Updated: 2025/12/09 13:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <stdlib.h>

void	destroy_mutexes(pthread_mutex_t *forks,
	pthread_mutex_t *print_mutex, int n_philos)
{
	int	i;

	if (forks)
	{
		i = 0;
		while (i < n_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
	if (print_mutex)
		pthread_mutex_destroy(print_mutex);
}

void	cleanup_resources(t_philosopher *philos,
	pthread_mutex_t *forks, t_rules *rules)
{
	if (philos && forks && rules)
		destroy_mutexes(forks, rules->print_mutex, rules->n_philos);
	if (forks)
		free(forks);
	if (rules->print_mutex)
		free(rules->print_mutex);
	if (rules->philosphers_finished_eating)
		free((void *)rules->philosphers_finished_eating);
	if (philos)
		free(philos);
}
