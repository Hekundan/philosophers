/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:19:01 by johartma          #+#    #+#             */
/*   Updated: 2025/05/25 20:15:02 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../philosophers.h"

static int	is_not_numeric(char *c)
{
	if (!c)
		return (-1);
	if (!*c)
		return (-1);
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (1);
		c++;
	}
	return (0);
}

static int	validate_args(int argn, char **argc)
{
	int	i;

	if (!(argn == 5 || argn == 6))
	{
		ft_printf("Wrong number of arguments\n");
		return (-1);
	}
	i = 1;
	while (i < argn)
	{
		if (is_not_numeric(*(argc + i)))
		{
			ft_printf("Argument %i is not numeric\n", i);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parse(int argn, char **argc, t_rules *rules)
{
	if (validate_args(argn, argc) == -1)
		return (-1);
	rules->n_philos = ft_atoi(argc[1]);
	rules->time_to_die = ft_atoi(argc[2]);
	rules->time_to_eat = ft_atoi(argc[3]);
	rules->time_to_sleep = ft_atoi(argc[4]);
	if (argn == 6)
		rules->times_required_to_eat = ft_atoi(argc[5]);
	else
		rules->times_required_to_eat = -1;
	return (0);
}
