/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:45 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/02 15:21:25 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*
** Standard macros redefined because the norme is a picky fucker.
*/

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LONG_MAX 9223372036854775807
# define TRUE 1
# define FALSE 0

/*
** Error return macros.
*/

# define TOO_FEW_ARGS "ERROR: One or more arguments missing."
# define TOO_MANY_ARGS "ERROR: There are too many arguments."
# define INPUT_TOO_HIGH "ERROR: Input is above the int limit"
# define INPUT_TOO_LOW "ERROR: Input is below 1."
# define NOT_DIGIT "ERROR: Input should be an integer."

/*
** Philosopher status macros.
*/

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DEAD 3

typedef struct s_args
{
	int	total_philos;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	total_meals;
}		t_args;

typedef struct s_philo
{
	int				index;
	int				status;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				meals_eaten;
	long long int	last_meal;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	long long int	session_start;
	pthread_mutex_t	*end_monitor;
}				t_philo;

typedef struct s_state
{
	t_args			*args;
	t_philo			*philos;
	pthread_mutex_t *forks;
	long long int	session_start;
}					t_state;

/*
** Auxiliary functions.
*/

int				ft_atoi(const char *str);
long long int	ft_atoll(char *str);
int				ft_isdigit(int c);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);

int				are_there_input_errors(int argc, char **argv);


#endif