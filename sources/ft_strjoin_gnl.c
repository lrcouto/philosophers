/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 16:24:45 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 02:50:42 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** This is a variation of ft_strjoin that works better with get_next_line.
** Libft memory allocations are commonly "protected" with a condition to return
** null if the allocation fails. This sometimes causes get_next_line to crash.
*/

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*str;
	size_t			s1_len;
	size_t			s2_len;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(*str));
	if (str == 0)
		return (0);
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		str[i] = s2[i - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}
