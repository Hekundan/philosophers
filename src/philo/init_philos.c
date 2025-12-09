/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:21:36 by johartma          #+#    #+#             */
/*   Updated: 2025/05/25 22:00:56 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../philosophers.h"
#include <pthread.h>
#include <stdlib.h>

static int	non_negative_mod(int a, int b)
{
	int	r;

	r = a % b;
	if (r < 0)
		return (r + b);
	return (r);
}

static void	init_philosopher_fields(t_philosopher *philo, int i,
	t_rules *rules, pthread_mutex_t *forks)
{
	philo->id = i;
	philo->rules = rules;
	philo->right_fork = forks + ((i - 1) % rules->n_philos);
	philo->left_fork = forks + non_negative_mod((i - 2), rules->n_philos);
	philo->died = false;
	philo->times_eaten = 0;
	philo->state = STATE_THINKING;
	philo->time_last_eat = rules->start_time;
	philo->time_state_change = rules->start_time;
}

int	init_philos(t_philosopher **philosphers,
		t_rules *rules, pthread_mutex_t **forks)
{
	int	i;

	*philosphers = ft_calloc(rules->n_philos, sizeof (t_philosopher));
	if (!*philosphers)
		return (-1);
	*forks = malloc(sizeof (pthread_mutex_t) * rules->n_philos);
	if (!*forks)
	{
		free(*philosphers);
		return (-1);
	}
	i = 1;
	while (i <= rules->n_philos)
	{
		init_philosopher_fields(&(*philosphers)[i - 1], i, rules, *forks);
		i++;
	}
	return (0);
}
