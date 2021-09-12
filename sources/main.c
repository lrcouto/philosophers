/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:17:34 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/11 20:56:25 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_args(char **argv, t_args *args)
{
	args->philos = ft_atoi(argv[1]);
	args->death_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		args->meals = ft_atoi(argv[5]);
	else
		args->meals = 0;
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (are_there_input_errors(argc, argv) == TRUE)
		return (-1);
	get_args(argv, &args);
	printf("%d\n%d\n%d\n%d\n%d\n", args.philos, args.death_time, args.eat_time, args.sleep_time, args.meals);
	return (0);
}
