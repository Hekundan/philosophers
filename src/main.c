/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:18:15 by johartma          #+#    #+#             */
/*   Updated: 2024/08/17 00:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include "../lib/libft/libft.h"
#include <stdlib.h>

int     main(int argn, char **argc)
{
        t_rules                 rules;
        t_philosopher           *philosphers;
        pthread_mutex_t         *forks;
        pthread_mutex_t         print_mutex;

        if (parse(argn, argc, &rules) == -1)
                return (-1);
        forks = NULL;
        philosphers = NULL;
        rules.print_mutex = &print_mutex;
        rules.exit_flag = false;
        if (pthread_mutex_init(rules.print_mutex, NULL))
        {
                ft_putstr_fd("Mutex init failed", 1);
                return (-1);
        }
        if (init_philos(&philosphers, &rules, &forks) == -1)
        {
                ft_putstr_fd("Malloc error", 1);
                return (-1);
        }
        if (init_mutex(forks, &rules) == -1)
                return (-1);
        rules.start_time = get_time();
        if (init_threads(philosphers) == -1)
                return (-1);
        join_threads(philosphers);
        pthread_mutex_destroy(rules.print_mutex);
        free(forks);
        free(philosphers);
        return (0);
}

