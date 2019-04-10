/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:21:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 11:51:22 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

void	stackdelone(t_stack **elem)
{
	t_stack *tmp;

	if (*elem)
	{
		if ((*elem)->next)
			(*elem)->next->prev = (*elem)->prev;
		if ((*elem)->prev)
			(*elem)->prev->next = (*elem)->next;
		tmp = (*elem)->next;
		ft_memdel((void**)elem);
		*elem = tmp;
	}
	*elem = 0;
}

void	stackdel(t_stack **elem)
{
	t_stack *tmp;

	if (!*elem)
		return ;
	tmp = *elem;
	if (tmp->prev)
	{
		while (tmp->prev)
		{
			tmp = (*elem)->prev;
			free(*elem);
			*elem = tmp;
		}
	}
	else
	{
		while (tmp->next)
		{
			tmp = (*elem)->next;
			free(*elem);
			*elem = tmp;
		}
	}
	free(*elem);
	*elem = 0;
}

int		ret_error(t_pushswap *ps)
{
	stackdel(&(ps->top_a));
	stackdel(&(ps->top_b));
	stackdel(&(ps->instruction_begin));
	ft_putendl_fd("Error", 2);
	return (-1);
}

static inline void	feed_index(t_pushswap *ps, int *tab, unsigned int size)
{
	unsigned int	i;
	t_stack *elem;

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

size_t	find_min_index(int option, t_pushswap *ps)
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

size_t	find_max_index(int option, t_pushswap *ps)
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

t_stack		*find_elem_index(int option, t_pushswap *ps, size_t index)
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

int		define_index(t_pushswap *ps)
{
	int				*tab;
	unsigned int	size;
	t_stack 		*elem;

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

void	find_max_min(t_stack *elem, int *max, int *min)
{
	t_stack *tmp;

	*max = INT_MIN;
	*min = INT_MAX;
	if (elem)
	{
		tmp = elem;
		while (tmp)
		{
			if (tmp->val > *max)
				*max = tmp->val;
			if (tmp->val < *min)
				*min = tmp->val;
			tmp = tmp->prev;
		}
	}
}

int		is_it_sorted(t_pushswap *ps, int option)
{
	t_stack	*tmp;

	tmp = (option == 'a') ? ps->top_a : ps->top_b;
	while (tmp)
	{
		if (!tmp->prev)
			return (1);
		else if (option == 'a' && tmp->prev->val < tmp->val)
			return (0);
		else if (option == 'b' && tmp->prev->val > tmp->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}
