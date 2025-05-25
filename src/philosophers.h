/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:38:41 by johartma          #+#    #+#             */
/*   Updated: 2025/05/25 22:01:01 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSPHERS_H
# include <stdbool.h>
# include <pthread.h>

typedef struct s_rules
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_required_to_eat;
	int					start_time;
	pthread_mutex_t		*print_mutex;
}	t_rules;

typedef struct s_philosopher
{
	int					id;
	int					time_last_eat;
	int					time_state_change;
	int					times_eaten;
	int					state;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_rules				*rules;
}	t_philosopher;

int	parse(int argn, char **argc, t_rules *rules);
int	init_philos(t_philosopher **philosphers,
		t_rules *rules, pthread_mutex_t **forks);

#endif