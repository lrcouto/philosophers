/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:45 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/11 19:25:21 by lcouto           ###   ########.fr       */
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

typedef struct s_args
{
	int	philos;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	meals;
}		t_args;

/*
** Auxiliary functions.
*/

int				ft_atoi(const char *str);
long long int	ft_atoll(char *str);
int				ft_isdigit(int c);
void			ft_putendl_fd(char *s, int fd);

int				are_there_input_errors(int argc, char **argv);

#endif