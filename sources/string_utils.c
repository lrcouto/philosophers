/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 02:19:56 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 17:49:02 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*copydest;
	char	*copysrc;

	i = 0;
	copydest = (char *)dest;
	copysrc = (char *)src;
	if ((!(dest) && !(src)) && (n > 0))
		return (NULL);
	while (i < n)
	{
		copydest[i] = copysrc[i];
		i++;
	}
	return (copydest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	if (!dest || !src)
		return (0);
	while (src[len] != '\0')
		++len;
	if (len + 1 < size)
		ft_memcpy(dest, (char *)src, len + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, (char *)src, size - 1);
		dest[size - 1] = '\0';
	}
	return (len);
}

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

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

void	ft_strdel(char **s)
{
	if (s == 0)
		return ;
	if (*s)
		free(*s);
	*s = 0;
}
