/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:34 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/29 23:03:37 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (long long int)1000 + time.tv_usec / (long long int)1000);
}

static long long int	timestamp(long long int session_start)
{
	return (get_time() - session_start);
}

static void	wait_time_in_ms(long long int time)
{
	usleep(time * 1000);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	printf("%lld | %s dropped their left fork.\n", timestamp(philo->session_start), philo->name);
	pthread_mutex_unlock(philo->right_fork);
	printf("%lld | %s dropped their right fork.\n", timestamp(philo->session_start), philo->name);
	philo->meals_eaten += 1;
	philo->last_meal = timestamp(philo->session_start);
}

static void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%lld | %s took a fork in their left hand.\n", timestamp(philo->session_start), philo->name);
	pthread_mutex_lock(philo->right_fork);
	printf("%lld | %s took a fork in their right hand.\n", timestamp(philo->session_start), philo->name);
	philo->status = EATING;
}

static int thinking(t_philo *philo)
{
	philo->status = THINKING;
	printf("%lld | %s is lost in though.\n", timestamp(philo->session_start), philo->name);
	return (TRUE);
}

static int sleeping(t_philo *philo)
{
	philo->status = SLEEPING;
	printf("%lld | %s is taking a nap. ZzZzZzZz.\n", timestamp(philo->session_start), philo->name);
	wait_time_in_ms(philo->sleep_time);
	return (TRUE);
}

static int eating(t_philo *philo)
{
	pick_up_forks(philo);
	printf("%lld | %s is eating! Yum!\n", timestamp(philo->session_start), philo->name);
	release_forks(philo);
	wait_time_in_ms(philo->eat_time);
	return (TRUE);
}

static void	join_threads(t_state *state, pthread_t *thread)
{
	int	i;

	i = 0;
	while(i < state->args->total_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

static void *routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo*)philo_pointer;
	while(eating(philo) && sleeping(philo) && thinking(philo))
		continue ;
	return (NULL);
}

static void	build_threads(t_state *state, pthread_t *thread)
{
	int		i;
	void	*current_philo;

	i = 0;
	while(i < state->args->total_philos)
	{
		current_philo = (void*)(&state->philos[i]);
		pthread_create(&thread[i], NULL, &routine, current_philo);
		pthread_detach(*thread);
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
		state->philos[i].left_fork = &state->forks[i];
		state->philos[i].right_fork = &state->forks[(i + 1) % state->args->total_philos];
		state->philos[i].sleep_time = state->args->sleep_time;
		state->philos[i].eat_time = state->args->eat_time;
		state->philos[i].death_time = state->args->death_time;	//TODO: Fix this disgusting mess.
		state->philos[i].session_start = state->session_start;
		i++;
	}
}

static void	init_forks(t_state *state)
{
	int	i;

	i = 0;
	state->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * state->args->total_philos);
	while (i < state->args->total_philos)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		i++;
	}
}

static void	init_state(t_state *state, t_args *args)
{
	pthread_t	thread[100];

	state->args = args;
	state->session_start = get_time();
	state->philos = (t_philo *)malloc(sizeof(t_philo) * args->total_philos);
	init_forks(state);
	init_philos(state);
	build_threads(state, thread);
	join_threads(state, thread);
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
