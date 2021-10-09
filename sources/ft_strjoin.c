/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 01:35:27 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/08 20:47:47 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sz;
	int		i;
	int		j;
	char	*joinedstr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sz = ft_strlen(s1) + ft_strlen(s2);
	joinedstr = malloc((sizeof(char) * sz) + 1);
	while (s1[i] != '\0')
	{
		joinedstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		joinedstr[i + j] = s2[j];
		j++;
	}
	joinedstr[i + j] = '\0';
	return (joinedstr);
}
