/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:45 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 17:34:42 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>

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
# define TOO_MANY_PHILOS "We don't need that many Ṕhilosophers. Put some back."
# define ZERO_PHILOS "If no one is there to eat the spaghetti, does it exist?"

/*
** Output definitions.
*/

# define THINKING 0
# define SLEEPING 1
# define EATING 2
# define PICK_LEFT_FORK 3
# define PICK_RIGHT_FORK 4
# define DROP_LEFT_FORK 5
# define DROP_RIGHT_FORK 6
# define SATIATED 7
# define DEAD 8

/*
** Color definitions.
*/

# define BLACK "\033[0;30m"
# define BOLD_BLACK "\033[1;30m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define BOLD_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define BOLD_CYAN "\033[1;36m"
# define WHITE "\033[0;37m"
# define BOLD_WHITE "\033[1;37m"
# define RESET_COLOR "\033[0m"

/*
** Program state & philosopher structs.
*/

typedef struct s_args
{
	int	total_philos;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	total_meals;
}		t_args;

typedef struct s_taken_names
{
	unsigned int			index;
	struct s_taken_names	*next;
}				t_taken_names;

typedef struct s_philo
{
	int				index;
	char			name[25];
	int				*death;
	char			*who_is_dead;
	long long int	*time_of_death;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				meals_eaten;
	int				*total_meals;
	long long int	last_meal;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	long long int	session_start;
	pthread_mutex_t	*end_monitor;
	pthread_mutex_t	*print_lock;
}				t_philo;

typedef struct s_state
{
	t_args			*args;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	char			who_is_dead[25];
	long long int	time_of_death;
	long long int	session_start;
	pthread_mutex_t	end_monitor;
	pthread_mutex_t	print_lock;
	int				death;
	t_taken_names	*taken_names;
}					t_state;

/*
** Auxiliary functions.
*/

int				ft_atoi(const char *str);
long long int	ft_atoll(char *str);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				get_next_line(int fd, char **line);
char			*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*ft_strdup_gnl(const char *s1);
char			*ft_strnew(size_t size);
void			ft_strdel(char **s);
char			*ft_strchr(const char *str, int c);
size_t			ft_strlen(const char *str);

/*
** Error handling.
*/

int				are_there_input_errors(int argc, char **argv);

/*
** Time handling.
*/

__uint64_t		get_time(void);
long long int	timestamp(long long int session_start);
void			wait_time_in_ms(long long int time);

/*
** Actions.
*/

int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
void			pick_up_forks(t_philo *philo);
void			pick_up_forks(t_philo *philo);

/*
** System & routines.
*/

int				is_philo_satiated(t_philo *philo);
void			init_state(t_state *state, t_args *args);
void			*routine(void *philo_pointer);

/*
** Output formatting.
*/

void			output(long long int timestamp, char *name,
					int type, int meals);

/*
** Philosopher name handlers.
*/

void			index_list_clear(t_state *state);
void			get_philo_name(char *name, t_state *state);

#endif