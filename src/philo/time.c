/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johartma <johartma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 00:00:00 by johartma          #+#    #+#             */
/*   Updated: 2024/08/17 00:00:00 by johartma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <sys/time.h>

int     get_time(void)
{
        struct timeval  time;

        if (gettimeofday(&time, NULL) == -1)
                return (-1);
        return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

