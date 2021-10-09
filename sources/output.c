/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:39:30 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 01:04:24 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	output(long long int timestamp, int index, int type, int meals)
{
	printf("% 10lld | ", timestamp);
	if (type == THINKING)
		printf("Philosopher %d is lost in though.\n", index);
	else if (type == SLEEPING)
		printf("Philosopher %d is taking a nap. ZzZzZzZz.\n", index);
	else if (type == EATING)
		printf("Philosopher %d is eating! Yum!\n", index);
	else if (type == PICK_LEFT_FORK)
		printf("Philosopher %d took a fork in their left hand.\n", index);
	else if (type == PICK_RIGHT_FORK)
		printf("Philosopher %d took a fork in their right hand.\n", index);
	else if (type == DROP_LEFT_FORK)
		printf("Philosopher %d dropped their left fork.\n", index);
	else if (type == DROP_RIGHT_FORK)
		printf("Philosopher %d dropped their right fork.\n", index);
	else if (meals > 0 && type == SATIATED)
		printf("Philosopher %d ate %d meals is now satiated!\n", index, meals);
	else if (type == DEAD)
		printf("Philosopher %d has starved to death\n", index);
}
