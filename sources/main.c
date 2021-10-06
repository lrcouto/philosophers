/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:34 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/05 22:38:34 by lcouto           ###   ########.fr       */
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

static int	is_philo_satiated(t_philo *philo)
{
	if (*philo->total_meals > 0 && philo->meals_eaten == *philo->total_meals)
		return (TRUE);
	return (FALSE);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d dropped their left fork.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d dropped their right fork.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	philo->meals_eaten += 1;
}

static void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d took a fork in their left hand.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d took a fork in their right hand.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	philo->last_meal = timestamp(philo->session_start);
}

static int thinking(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d is lost in though.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	return (TRUE);
}

static int sleeping(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d is taking a nap. ZzZzZzZz.\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
	wait_time_in_ms(philo->sleep_time);
	return (TRUE);
}

static int eating(t_philo *philo)
{
	if (*philo->death == TRUE || is_philo_satiated(philo) == TRUE)
		return (FALSE);
	pick_up_forks(philo);
	pthread_mutex_lock(philo->print_lock);
	printf("%lld | Philosopher %d is eating! Yum!\n", timestamp(philo->session_start), philo->index);
	pthread_mutex_unlock(philo->print_lock);
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

static void	*monitor_end(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo*)philo_pointer;
	while (1)
	{
		if (is_philo_satiated(philo) == TRUE)
		{
			printf("%lld | Philosopher %d ate %d meals is now satiated!\n", timestamp(philo->session_start), philo->index, philo->meals_eaten);
			return ((void *)1);
		}
		if ((timestamp(philo->session_start) - philo->last_meal) > philo->death_time)
		{
			if (*philo->death == FALSE)
			{
				pthread_mutex_lock(philo->print_lock);
				printf("%lld | Philosopher %d has starved to death\n", timestamp(philo->session_start), philo->index);
				pthread_mutex_unlock(philo->print_lock);
			}
			pthread_mutex_lock(philo->end_monitor);
			*philo->death = TRUE;
			pthread_mutex_unlock(philo->end_monitor);
			return ((void *)1);
		}
	}
}

static void *routine(void *philo_pointer)
{
	t_philo		*philo;
	pthread_t	end;

	philo = (t_philo*)philo_pointer;
	if (pthread_create(&end, NULL, &monitor_end, philo) != 0)
		return((void *)1);
	pthread_detach(end);
	if (philo->index % 2 == 0)
		usleep(100);
	while(eating(philo) && sleeping(philo) && thinking(philo))
		continue ;
	return (NULL);
}

static int	build_threads(t_state *state, pthread_t *thread)
{
	int		i;
	void	*current_philo;

	i = 0;
	while(i < state->args->total_philos)
	{
		current_philo = (void*)(&state->philos[i]);
		if (pthread_create(&thread[i], NULL, &routine, current_philo) != 0)
			return(1);
		pthread_detach(*thread);
		i++;
	}
	return (0);
}

static void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while(i< state->args->total_philos)
	{
		state->philos[i].index = i + 1;
		state->philos[i].meals_eaten = 0;
		state->philos[i].death = &state->death;
		state->philos[i].last_meal = 0;
		state->philos[i].left_fork = &state->forks[i];
		state->philos[i].right_fork = &state->forks[(i + 1) % state->args->total_philos];
		state->philos[i].sleep_time = state->args->sleep_time;
		state->philos[i].eat_time = state->args->eat_time;
		state->philos[i].death_time = state->args->death_time;	//TODO: Fix this disgusting mess.
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

static int	init_state(t_state *state, t_args *args)
{
	pthread_t	thread[100];

	state->args = args;
	state->session_start = get_time();
	state->death = FALSE;
	pthread_mutex_init(&state->end_monitor, NULL);
	pthread_mutex_init(&state->print_lock, NULL);
	init_forks(state);
	init_philos(state);
	if (build_threads(state, thread) != 0)
		return (1);
	join_threads(state, thread);
	return (0);
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
	if (init_state(&state, &args) != 0)
		return(1);
	return (0);
}
