/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 01:24:01 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 03:13:44 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	index_list_clear(t_state *state)
{
	t_taken_names	*aux;
	t_taken_names	*temp;

	aux = state->taken_names;
	if (aux == NULL)
		return ;
	while (aux != NULL)
	{
		temp = aux->next;
		free(aux);
		aux = temp;
	}
	state->taken_names = NULL;
}

static char	*get_name(char *name, unsigned int index)
{
	char			*filename;
	char			*philo_name;
	int				fd;
	unsigned int	i;

	filename = "sources/names.txt";
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((get_next_line(fd, &philo_name) == 1))
	{
		if (i == index)
			break ;
		free(philo_name);
		i++;
	}
	if (philo_name)
		ft_strlcpy(name, philo_name, sizeof(philo_name));
	close(fd);
	free(philo_name);
	exit(0);
}

static void	add_new_node(t_taken_names *taken, unsigned int	index)
{
	t_taken_names	*new;
	t_taken_names	*current;

	new = (t_taken_names *)malloc(sizeof(t_taken_names));
	new->index = index;
	current = taken;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	current->next->next = NULL;
}

static unsigned int get_random_index(void)
{
	unsigned long long	next;

	next = get_time() * 1103515245 + 12345;
	return ((unsigned int)(next/655369) % 200);
}

void	get_philo_name(char *name, t_taken_names *taken)
{
	unsigned int	index;
	t_taken_names	*current;
	
	index = get_random_index();
	current = taken;
	while (current->index != index)
	{
		if (current->index == index)
		{
			index = get_random_index();
			current = taken;
			continue ;
		}
		current = current->next;
	}
	add_new_node(taken, index);
	get_name(name, index);
}