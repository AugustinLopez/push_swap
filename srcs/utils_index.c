/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:18:16 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:16:56 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

size_t				find_min_index(int option, t_pushswap *ps)
{
	t_stack *elem;
	size_t	min;

	min = INT_MAX;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->index < min)
			min = elem->index;
		elem = elem->prev;
	}
	return (min);
}

size_t				find_max_index(int option, t_pushswap *ps)
{
	t_stack *elem;
	size_t	max;

	max = 0;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->index > max)
			max = elem->index;
		elem = elem->prev;
	}
	return (max);
}

t_stack				*find_elem_index(int option, t_pushswap *ps, size_t index)
{
	t_stack *elem;

	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->index == index)
			return (elem);
		elem = elem->prev;
	}
	return (NULL);
}

static inline void	feed_index(t_pushswap *ps, int *tab, unsigned int size)
{
	unsigned int	i;
	t_stack			*elem;

	elem = ps->top_a;
	while (elem)
	{
		i = 0;
		while (i < size)
		{
			if (tab[i] == elem->val)
			{
				elem->index = i;
				break ;
			}
			i++;
		}
		elem = elem->prev;
	}
}

int					define_index(t_pushswap *ps)
{
	int				*tab;
	unsigned int	size;
	t_stack			*elem;

	if (!(tab = (int *)malloc(sizeof(int) * ps->a)))
		return (0);
	size = 0;
	elem = ps->top_a;
	while (elem)
	{
		tab[size++] = elem->val;
		elem = elem->prev;
	}
	ft_quicksort(&tab, 0, size - 1);
	feed_index(ps, tab, size);
	free(tab);
	return (1);
}
