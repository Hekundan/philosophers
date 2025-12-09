/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:00:00 by johartma          #+#    #+#             */
/*   Updated: 2025/12/09 13:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <sys/time.h>
#include <unistd.h>

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long duration_ms)
{
	long	start;
	long	current;

	start = get_time_ms();
	while (1)
	{
		current = get_time_ms();
		if (current - start >= duration_ms)
			break ;
		if (current - start < duration_ms - 10)
			usleep(1000);
		else
			usleep(100);
	}
}

int	time_since(long start_time)
{
	return ((int)(get_time_ms() - start_time));
}
