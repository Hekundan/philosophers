/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:00:00 by johartma          #+#    #+#             */
/*   Updated: 2025/12/09 13:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	lock_forks_ordered(t_philosopher *philo,
	pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (philo->id % 2 == 1)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

int	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->rules->exit_flag)
		return (-1);
	lock_forks_ordered(philo, &first, &second);
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	if (philo->rules->n_philos == 1)
	{
		pthread_mutex_unlock(first);
		return (-1);
	}
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
	return (0);
}

void	eat_action(t_philosopher *philo)
{
	philo->state = STATE_EATING;
	philo->time_state_change = get_time_ms();
	philo->time_last_eat = philo->time_state_change;
	safe_print(philo, "is eating");
	precise_sleep(philo->rules->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->rules->times_required_to_eat != -1
		&& philo->times_eaten >= philo->rules->times_required_to_eat)
	{
		(*philo->rules->philosphers_finished_eating)++;
	}
}

void	sleep_action(t_philosopher *philo)
{
	philo->state = STATE_SLEEPING;
	philo->time_state_change = get_time_ms();
	safe_print(philo, "is sleeping");
	precise_sleep(philo->rules->time_to_sleep);
}

void	think_action(t_philosopher *philo)
{
	philo->state = STATE_THINKING;
	philo->time_state_change = get_time_ms();
	safe_print(philo, "is thinking");
}
