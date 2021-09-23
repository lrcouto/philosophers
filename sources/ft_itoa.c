/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:36:50 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/23 01:37:05 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_return_len(unsigned int n)
{
	unsigned int	len;

	len = 0;
	while (n >= 10)
	{
		n /= 10;
		++len;
	}
	return (len + 1);
}

static char	*itoa_loop(unsigned int	nb, char *str, unsigned int len)
{
	int	i;

	i = len - 1;
	while (nb >= 10)
	{
		str[i--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[i] = (char)(nb % 10 + 48);
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	unsigned int	len;

	if (n < 0)
		nb = (unsigned int)(n * -1);
	else
		nb = (unsigned int)n;
	len = (unsigned int)get_return_len(nb);
	if (n < 0)
		str = (char *)malloc(sizeof(char) * (len + 1 + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (n < 0)
	{
		str[0] = '-';
		len++;
	}
	return (itoa_loop(nb, str, len));
}