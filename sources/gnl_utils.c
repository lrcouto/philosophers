/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 16:14:49 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 17:49:21 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

/*
** This is a slight variation of ft_substr that works better with get_next_line.
** Libft memory allocations are commonly "protected" with a condition to return
** null if the allocation fails. This sometimes causes get_next_line to crash.
*/

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			s_len;

	i = 0;
	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup_gnl(""));
	sub = (char *)malloc((len + 1) * sizeof(*s));
	if (sub == 0)
		return (0);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

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

/*
** This is a slight variation of ft_strdup that works better with get_next_line.
** Libft memory allocations are commonly "protected" with a condition to return
** null if the allocation fails. This sometimes causes get_next_line to crash.
*/

char	*ft_strdup_gnl(const char *s1)
{
	char			*copy;
	unsigned int	i;
	unsigned int	s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	copy = (char *)malloc((s1_len + 1) * sizeof(*copy));
	if (copy == 0)
		return (0);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
