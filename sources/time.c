/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:47:41 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/08 20:28:02 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (__uint64_t)1000 + time.tv_usec / (__uint64_t)1000);
}

long long int	timestamp(long long int session_start)
{
	return (get_time() - session_start);
}

void	wait_time_in_ms(long long int time)
{
	usleep(time * 1000);
}
