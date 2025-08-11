/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:28:35 by johartma          #+#    #+#             */
/*   Updated: 2024/08/17 00:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include "../../lib/libft/libft.h"
#include <unistd.h>

static void     print_state(t_philosopher *philo, char *msg)
{
        int     time;

        time = get_time() - philo->rules->start_time;
        pthread_mutex_lock(philo->rules->print_mutex);
        if (!philo->rules->exit_flag)
                ft_printf("%i %i %s\n", time, philo->id, msg);
        pthread_mutex_unlock(philo->rules->print_mutex);
}

static void     philo_eat(t_philosopher *philo)
{
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
        print_state(philo, "is eating");
        philo->time_last_eat = get_time();
        usleep(philo->rules->time_to_eat * 1000);
        philo->times_eaten++;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
}

static void     philo_sleep(t_philosopher *philo)
{
        print_state(philo, "is sleeping");
        usleep(philo->rules->time_to_sleep * 1000);
        print_state(philo, "is thinking");
}

void    *philo_routine(void *var)
{
        t_philosopher   *philo;
        int             required;

        philo = (t_philosopher *)var;
        required = philo->rules->times_required_to_eat;
        if (required == 0)
                return (NULL);
        if (philo->id % 2 == 0)
                usleep(1000);
        while (!philo->rules->exit_flag &&
                (required == -1 || philo->times_eaten < required))
        {
                philo_eat(philo);
                if (required != -1 && philo->times_eaten >= required)
                        break ;
                philo_sleep(philo);
        }
        return (NULL);
}

