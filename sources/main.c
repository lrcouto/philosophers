/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:34 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/23 01:52:19 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo*)philo_pointer;
	while(1)
	{
		printf("%s is thinking...\n", philo->name);
	}
}

static void	build_threads(t_state *state)
{
	int			i;
	pthread_t	thread;
	void		*current_philo;

	i = 0;
	while(i < state->args->total_philos)
	{
		current_philo = (void*)(&state->philos[i]);
		pthread_create(&thread, NULL, &routine, current_philo);
		i++;
	}
}

static void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while(i< state->args->total_philos)
	{
		state->philos[i].name = ft_strjoin("Philosopher ", ft_itoa(i));	//TODO: make name selector just because it's cool.
		state->philos[i].meals_eaten = 0;
		state->philos[i].status = THINKING;
		state->philos[i].last_meal = 0;
		state->philos[i].left_hand = i;
		state->philos[i].right_hand = (i + 1) % state->args->total_philos;
		i++;
	}
}

static void	init_state(t_state *state, t_args *args)
{
	state->args = args;
	state->philos = (t_philo *)malloc(sizeof(t_philo) * args->total_philos);
	init_philos(state);
	build_threads(state);
}

static void	get_args(char **argv, t_args *args)
{
	args->total_philos = ft_atoi(argv[1]);
	args->death_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		args->total_meals = ft_atoi(argv[5]);
	else
		args->total_meals = 0;
}

int	main(int argc, char **argv)
{
	t_state	state;
	t_args	args;

	if (are_there_input_errors(argc, argv) == TRUE)
		return (-1);
	get_args(argv, &args);
	init_state(&state, &args);
	return (0);
}
