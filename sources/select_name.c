/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 01:24:01 by lcouto            #+#    #+#             */
/*   Updated: 2021/10/09 15:35:57 by lcouto           ###   ########.fr       */
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

static void	get_name(char *name, unsigned int index)
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
		ft_strlcpy(name, philo_name, 25);
	close(fd);
	free(philo_name);
}

static void	add_new_node(t_state *state, unsigned int index)
{
	t_taken_names	*new;
	t_taken_names	*current;

	new = (t_taken_names *)malloc(sizeof(t_taken_names));
	new->index = index;
	current = state->taken_names;
	while (current && current->next != NULL)
		current = current->next;
	if (!current)
	{
		state->taken_names = new;
		state->taken_names->next = NULL;
	}
	else
	{
		current->next = new;
		current->next->next = NULL;
	}
}

static unsigned int	get_random_index(void)
{
	unsigned long long	next;

	next = get_time() * 1103515245 + 12345;
	return ((unsigned int)(next / 655369) % 200);
}

void	get_philo_name(char *name, t_state *state)
{
	unsigned int	index;
	t_taken_names	*current;

	index = get_random_index();
	current = state->taken_names;
	while (current && current->index != index)
	{
		if (current->index == index)
		{
			index = get_random_index();
			current = state->taken_names;
			continue ;
		}
		current = current->next;
	}
	add_new_node(state, index);
	get_name(name, index);
}
