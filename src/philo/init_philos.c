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
		(*philosphers)[i - 1].id = i;
		(*philosphers)[i - 1].rules = rules;
		(*philosphers)[i - 1].right_fork = (*forks)
			+ ((i - 1) % rules->n_philos);
		(*philosphers)[i - 1].left_fork = (*forks)
			+ non_negative_mod((i - 2), rules->n_philos);
		i++;
	}
	return (0);
}
