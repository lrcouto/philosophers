/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:50:14 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/05 21:48:55 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_message(char *message)
{
	printf("%s%s%s\n", "\033[1;33m", message, "\033[0m");
}

static int	invalid_philo_number(int number)
{
	if (number > 200)
	{
		error_message(TOO_MANY_PHILOS);
		return (TRUE);
	}
	if (number == 0)
	{
		error_message(ZERO_PHILOS);
		return (TRUE);
	}
	if (number == 1)
	{
		printf("\033[0;33m");
		printf("The lone Philosopher contemplates the meaninglessness\n");
		printf("of his existence, as he slowly starves to death with\n");
		printf("the large plate of spaghetti just out of his reach,\n");
		printf("tantalizing yet untouchable. If only he had another fork.\n");
		printf("\033[0m");
		return (TRUE);
	}
	return (FALSE);
}

static int	check_int_limit(char *current_arg)
{
	long long int	current_number;

	current_number = ft_atoll(current_arg);
	if (current_number > INT_MAX)
	{
		error_message(INPUT_TOO_HIGH);
		return (TRUE);
	}
	else if (current_number < 1)
	{
		error_message(INPUT_TOO_LOW);
		return (TRUE);
	}
	return (FALSE);
}

static int	check_for_digits(char *current_arg)
{
	int	i;

	i = 0;
	if (current_arg[0] == '-' || current_arg[0] == '+')
		i = 1;
	while (current_arg[i])
	{
		if (ft_isdigit((int)current_arg[i]) == 0)
		{
			error_message(NOT_DIGIT);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	are_there_input_errors(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
	{
		error_message(TOO_FEW_ARGS);
		return (TRUE);
	}
	if (argc > 6)
	{
		error_message(TOO_MANY_ARGS);
		return (TRUE);
	}
	if (invalid_philo_number(ft_atoi(argv[1])) == TRUE)
		return (TRUE);
	while (argv[i])
	{
		if (check_for_digits(argv[i]) == TRUE
			|| check_int_limit(argv[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
