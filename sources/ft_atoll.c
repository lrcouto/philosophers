/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:40:19 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/11 19:25:43 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_count_spaces(const char *str, int i)
{
	while ((str[i] == '\t') || (str[i] == '\v') || (str[i] == '\f')
		|| (str[i] == '\r') || (str[i] == '\n') || (str[i] == ' '))
	{
		i++;
	}
	return (i);
}

long long int	ft_atoll(char *str)
{
	int				i;
	long long int	is_negative;
	long long int	result;

	i = 0;
	is_negative = 1;
	result = 0;
	i = ft_count_spaces(str, i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= 48) && (str[i] <= 57))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (is_negative * result);
}
