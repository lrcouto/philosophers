/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:39:30 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 17:26:30 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	select_color(char *color, int type)
{
	if (type == THINKING)
		ft_strlcpy(color, BOLD_BLUE, 10);
	else if (type == SLEEPING)
		ft_strlcpy(color, BOLD_CYAN, 10);
	else if (type == EATING)
		ft_strlcpy(color, BOLD_GREEN, 10);
	else if (type == PICK_LEFT_FORK)
		ft_strlcpy(color, GREEN, 10);
	else if (type == PICK_RIGHT_FORK)
		ft_strlcpy(color, GREEN, 10);
	else if (type == DROP_LEFT_FORK)
		ft_strlcpy(color, CYAN, 10);
	else if (type == DROP_RIGHT_FORK)
		ft_strlcpy(color, CYAN, 10);
	else if (type == SATIATED)
		ft_strlcpy(color, BOLD_PURPLE, 10);
	else if (type == DEAD)
		ft_strlcpy(color, BOLD_RED, 10);
}

void	output(long long int timestamp, char *name, int type, int meals)
{
	char	color[10];

	select_color(color, type);
	printf("%s", color);
	printf("% 10lld | ", timestamp);
	if (type == THINKING)
		printf("%s is lost in though.\n", name);
	else if (type == SLEEPING)
		printf("%s is taking a nap. ZzZzZzZz.\n", name);
	else if (type == EATING)
		printf("%s is eating! Yum!\n", name);
	else if (type == PICK_LEFT_FORK)
		printf("%s took a fork in their left hand.\n", name);
	else if (type == PICK_RIGHT_FORK)
		printf("%s took a fork in their right hand.\n", name);
	else if (type == DROP_LEFT_FORK)
		printf("%s dropped their left fork.\n", name);
	else if (type == DROP_RIGHT_FORK)
		printf("%s dropped their right fork.\n", name);
	else if (type == SATIATED)
		printf("%s ate %d meals and is now satiated!\n", name, meals);
	else if (type == DEAD)
		printf("%s has starved to death\n", name);
	printf("%s", RESET_COLOR);
}
