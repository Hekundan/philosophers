/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:38:41 by johartma          #+#    #+#             */
/*   Updated: 2025/05/26 17:43:43 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdbool.h>
# include <pthread.h>

# define STATE_THINKING 0
# define STATE_EATING 1
# define STATE_SLEEPING 2
# define STATE_DEAD 3

typedef struct s_rules
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_required_to_eat;
	long				start_time;
	volatile int		*philosphers_finished_eating;
	volatile bool		exit_flag;
	pthread_mutex_t		*print_mutex;
}	t_rules;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	bool				died;
	long				time_last_eat;
	long				time_state_change;
	int					times_eaten;
	int					state;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_rules				*rules;
}	t_philosopher;

int		parse(int argn, char **argc, t_rules *rules);
int		init_philos(t_philosopher **philosphers,
			t_rules *rules, pthread_mutex_t **forks);
void	*philo_routine(void *var);
int		init_mutex(pthread_mutex_t *forks, t_rules *rules);
int		init_threads(t_philosopher *philosopher);
int		init_rules_mutexes(t_rules *rules);

long	get_time_ms(void);
void	precise_sleep(long duration_ms);
int		time_since(long start_time);

void	safe_print(t_philosopher *philo, char *message);
void	print_death(t_philosopher *philo);

int		take_forks(t_philosopher *philo);
void	eat_action(t_philosopher *philo);
void	sleep_action(t_philosopher *philo);
void	think_action(t_philosopher *philo);

void	*monitor_routine(void *arg);
int		check_simulation_end(t_rules *rules);

void	cleanup_resources(t_philosopher *philos,
			pthread_mutex_t *forks, t_rules *rules);
void	destroy_mutexes(pthread_mutex_t *forks,
			pthread_mutex_t *print_mutex, int n_philos);

#endif
