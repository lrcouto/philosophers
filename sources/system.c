/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:31:38 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 01:13:11 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_state *state, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < state->args->total_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

static int	build_threads(t_state *state, pthread_t *thread)
{
	int		i;
	void	*current_philo;

	i = 0;
	while (i < state->args->total_philos)
	{
		current_philo = (void *)(&state->philos[i]);
		if (pthread_create(&thread[i], NULL, &routine, current_philo) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->args->total_philos)
	{
		state->philos[i].index = i + 1;
		state->philos[i].meals_eaten = 0;
		state->philos[i].death = &state->death;
		state->philos[i].who_is_dead = &state->who_is_dead;
		state->philos[i].time_of_death = &state->time_of_death;
		state->philos[i].last_meal = 0;
		state->philos[i].left_fork = &state->forks[i];
		state->philos[i].right_fork = &state->forks[(i + 1)
			% state->args->total_philos];
		state->philos[i].sleep_time = state->args->sleep_time;
		state->philos[i].eat_time = state->args->eat_time;
		state->philos[i].death_time = state->args->death_time;
		state->philos[i].total_meals = &state->args->total_meals;
		state->philos[i].session_start = state->session_start;
		state->philos[i].end_monitor = &state->end_monitor;
		state->philos[i].print_lock = &state->print_lock;
		i++;
	}
}

static void	init_forks(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->args->total_philos)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		i++;
	}
}

void	init_state(t_state *state, t_args *args)
{
	pthread_t	thread[200];

	state->args = args;
	state->session_start = get_time();
	state->time_of_death = 0;
	state->death = FALSE;
	state->who_is_dead = 0;
	pthread_mutex_init(&state->end_monitor, NULL);
	pthread_mutex_init(&state->print_lock, NULL);
	init_forks(state);
	init_philos(state);
	build_threads(state, thread);
	join_threads(state, thread);
}
