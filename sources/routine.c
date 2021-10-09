/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:37:48 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 16:06:57 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_satiated(t_philo *philo)
{
	if (*philo->total_meals > 0 && philo->meals_eaten == *philo->total_meals)
		return (TRUE);
	return (FALSE);
}

static void	satiation_sequence(t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	output(timestamp(philo->session_start), philo->name,
		SATIATED, philo->meals_eaten);
	pthread_mutex_unlock(philo->print_lock);
}

static void	death_sequence(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	*philo->death = TRUE;
	*philo->time_of_death = timestamp(philo->session_start);
	ft_strlcpy(philo->who_is_dead, philo->name, 25);
}

static void	*monitor_end(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (1)
	{
		if (*philo->death == TRUE)
			return ((void *)1);
		if (is_philo_satiated(philo) == TRUE)
		{
			satiation_sequence(philo);
			return ((void *)1);
		}
		if ((timestamp(philo->session_start) - philo->last_meal)
			> philo->death_time && *philo->death == FALSE)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_lock(philo->end_monitor);
			death_sequence(philo);
			pthread_mutex_unlock(philo->end_monitor);
			return ((void *)1);
		}
	}
}

void	*routine(void *philo_pointer)
{
	t_philo		*philo;
	pthread_t	end;

	philo = (t_philo *)philo_pointer;
	if (pthread_create(&end, NULL, &monitor_end, philo) != 0)
		return ((void *)1);
	pthread_detach(end);
	if (philo->index % 2 == 0)
		usleep(6000);
	while (eating(philo) && sleeping(philo) && thinking(philo))
		continue ;
	return (NULL);
}
