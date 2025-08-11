/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 00:00:00 by johartma          #+#    #+#             */
/*   Updated: 2024/08/17 00:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/philosophers.h"
#include "../lib/libft/libft.h"
#include <assert.h>
#include <stdlib.h>

static void     test_parse(void)
{
        t_rules rules;
        char    *argv1[] = {"prog", "3", "400", "100", "100", NULL};

        assert(parse(5, argv1, &rules) == 0);
        assert(rules.n_philos == 3);
        assert(rules.time_to_die == 400);
        assert(rules.time_to_eat == 100);
        assert(rules.time_to_sleep == 100);
        char    *argv2[] = {"prog", "a", "1", "1", "1", NULL};
        assert(parse(5, argv2, &rules) == -1);
}

static void     test_init_philos(void)
{
        t_rules         rules;
        t_philosopher   *philos;
        pthread_mutex_t *forks;

        rules.n_philos = 2;
        assert(init_philos(&philos, &rules, &forks) == 0);
        assert(philos[0].id == 1);
        assert(philos[1].id == 2);
        assert(philos[0].right_fork == &forks[0]);
        assert(philos[0].left_fork == &forks[1]);
        free(philos);
        free(forks);
}

static void     test_init_mutex(void)
{
        t_rules         rules;
        t_philosopher   *philos;
        pthread_mutex_t *forks;

        rules.n_philos = 2;
        assert(init_philos(&philos, &rules, &forks) == 0);
        assert(init_mutex(forks, &rules) == 0);
        assert(pthread_mutex_lock(&forks[0]) == 0);
        assert(pthread_mutex_unlock(&forks[0]) == 0);
        free(philos);
        free(forks);
}

static void     test_threads_and_routine(void)
{
        t_rules         rules;
        t_philosopher   *philos;
        pthread_mutex_t *forks;
        pthread_mutex_t print_mutex;

        rules.n_philos = 2;
        rules.time_to_die = 1000;
        rules.time_to_eat = 10;
        rules.time_to_sleep = 10;
        rules.times_required_to_eat = 1;
        rules.exit_flag = false;
        rules.print_mutex = &print_mutex;
        pthread_mutex_init(rules.print_mutex, NULL);
        assert(init_philos(&philos, &rules, &forks) == 0);
        assert(init_mutex(forks, &rules) == 0);
        rules.start_time = get_time();
        assert(init_threads(philos) == 0);
        assert(join_threads(philos) == 0);
        assert(philos[0].times_eaten == 1);
        assert(philos[1].times_eaten == 1);
        pthread_mutex_destroy(rules.print_mutex);
        free(philos);
        free(forks);
}

int     main(void)
{
        test_parse();
        test_init_philos();
        test_init_mutex();
        test_threads_and_routine();
        ft_printf("All tests passed\n");
        return (0);
}

