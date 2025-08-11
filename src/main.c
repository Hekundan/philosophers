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

int	main(int argn, char **argc)
{
	volatile t_rules	rules;
	t_philosopher		*philosphers;
	pthread_mutex_t		*forks;

	if (parse(argn, argc, &rules) == -1)
		return (-1);
	forks = NULL;
	philosphers = NULL;
	if (init_philos(&philosphers, &rules, &forks) == -1)
	{
		ft_putstr_fd("Malloc error", 1);
		return (-1);
	}
	return (0);
}
