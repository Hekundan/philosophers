/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:18:15 by johartma          #+#    #+#             */
/*   Updated: 2025/05/26 17:39:10 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>

static void	join_threads(t_philosopher *philosophers, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int argn, char **argc)
{
	t_rules			rules;
	t_philosopher	*philosphers;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;

	if (parse(argn, argc, &rules) == -1)
		return (-1);
	if (init_rules_mutexes(&rules) == -1)
		return (ft_putstr_fd("Rules initialization failed\n", 2), -1);
	forks = NULL;
	philosphers = NULL;
	if (init_philos(&philosphers, &rules, &forks) == -1)
		return (cleanup_resources(NULL, NULL, &rules),
			ft_putstr_fd("Malloc error\n", 2), -1);
	if (init_mutex(forks, &rules) == -1)
		return (cleanup_resources(philosphers, forks, &rules), -1);
	if (init_threads(philosphers) == -1)
		return (cleanup_resources(philosphers, forks, &rules), -1);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philosphers))
		return (rules.exit_flag = true,
			cleanup_resources(philosphers, forks, &rules), -1);
	pthread_join(monitor_thread, NULL);
	join_threads(philosphers, rules.n_philos);
	cleanup_resources(philosphers, forks, &rules);
	return (0);
}
