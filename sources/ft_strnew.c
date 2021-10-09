/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:31:52 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 02:54:49 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
