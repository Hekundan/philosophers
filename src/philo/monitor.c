/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:00:00 by johartma          #+#    #+#             */
/*   Updated: 2025/12/09 13:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <unistd.h>

static int	check_death(t_philosopher *philos, t_rules *rules)
{
	int		i;
	long	current_time;
	long	time_since_eat;

	i = 0;
	current_time = get_time_ms();
	while (i < rules->n_philos)
	{
		if (philos[i].state == STATE_EATING)
		{
			i++;
			continue ;
		}
		time_since_eat = current_time - philos[i].time_last_eat;
		if (time_since_eat > rules->time_to_die)
		{
			philos[i].died = true;
			rules->exit_flag = true;
			print_death(&philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_simulation_end(t_rules *rules)
{
	if (rules->times_required_to_eat == -1)
		return (0);
	if (*rules->philosphers_finished_eating >= rules->n_philos)
	{
		rules->exit_flag = true;
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philosopher	*philos;
	t_rules			*rules;

	philos = (t_philosopher *)arg;
	rules = philos[0].rules;
	while (!rules->exit_flag)
	{
		if (check_death(philos, rules))
			break ;
		if (check_simulation_end(rules))
			break ;
		usleep(1000);
	}
	return (NULL);
}
