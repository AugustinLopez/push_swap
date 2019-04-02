/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:37:29 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/02 19:00:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

t_stack		*find_elem(int option, t_pushswap *ps, size_t index)
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

size_t	find_min(int option, t_pushswap *ps)
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

size_t	find_max(int option, t_pushswap *ps)
{
	t_stack *elem;
	size_t	max;
	
	min = 0;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->index > max)
			max = elem->index;
		elem = elem->prev;
	}
	return (max);
}

size_t		mode_incremental(t_pushswap *ps, size_t index)
{
	size_t	i;
	t_stack	*elem;
	t_stack *best;
	size_t	mem;

	if (!ps->a)
		return (0);
	best = find_elem('a', ps, index);
	elem = (best->prev) ? best->prev : ps->top_a;
	best->val = 1;
	i = 1;
	mem = best->index;
	while (elem != best)
	{
		if (elem->index == mem + 1)
		{
			elem->val = 1;
			mem = elem->index;
			i++;
		}
		else
			elem->val = 0;
		elem = (elem->prev) ? elem->prev : ps->top_a;
	}
	return (i);
}

size_t		mode_greater(t_pushswap *ps, size_t index)
{
	size_t	i;
	t_stack *elem;
	t_stack *best;
	size_t	mem;

	if (!ps->a)
		return (0);
	best = find_elem('a', ps, index);
	elem = (best->prev) ? best->prev : ps->top_a;
	best->val = 1;
	i = 1;
	mem = best->index;
	while (elem != best)
	{
		if (elem->index > mem)
		{
			elem->val = 1;
			mem = elem->index;
			i++;
		}
		else
			elem->val = 0;
		elem = (elem->prev) ? elem->prev : ps->top_a;
	}
	return (i);
}

static inline int	needs_pb(t_pushswap *ps)
{
	t_stack	*elem;

	if (ps->a < 1)
		return (0);
	elem = ps->top_a;
	while (elem)
	{
		if (elem->val == 0)
			return (1);
		elem = elem->prev;
	}
	return (0);
}

static inline int	needs_sa(t_pushswap *ps, size_t best, size_t (*mode)(t_pushswap *, size_t))
{
	size_t	i;
	size_t	j;

	if (ps->a < 2)
		return (0);
	if (!ps_operand(ps, SA, 1))
		return (-1);
	j = mode(ps, best);
	if (!ps_operand(ps, SA, 1))
		return (-1);
	i = mode(ps, best);
	if (i < j)
		return (1);
	return (0);
}

static inline int	is_it_indexed(t_pushswap *ps, int option)
{
	t_stack *tmp;

	tmp = (option == 'a') ? ps->top_a : ps->top_b;
	while (tmp)
	{
		if (!tmp->prev)
			return (1);
		else if (option == 'a' && tmp->prev->index < tmp->index)
			return (0);
		else if (option == 'b' && tmp->prev->index > tmp->index)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

size_t		find_best_index(t_pushswap *ps, size_t (*mode)(t_pushswap *, size_t))
{
	size_t	k;
	size_t	i;
	size_t	j;
	t_stack	*best;

	if (!ps->a)
		return (0);
	best = ps->top_a;
	i = 0;
	k = 0;
	while (i++ < ps->a)
	{
		j = mode(ps, ps->top_a->index);
		if (j >= k && ps->top_a->index < best->index)
		{
			k = j;
			best = ps->top_a;
		}
		ps_operand(ps, RA, 1);
	}
	stackdel(&ps->instruction_begin);
	mode(ps, best->index);
	return (best->index);
}


int			sort_a(t_pushswap *ps, size_t best, size_t (*mode)(t_pushswap *, size_t))
{
	int	i;

	while (needs_pb(ps))
	{
		if ((i = needs_sa(ps, best, mode)))
		{
			if (i == -1 || !ps_operand(ps, SA, 1))
				return (0);
			mode(ps, best);
		}
		else if (ps->top_a->val == 0)
		{
			if (!ps_operand(ps, PB, 1))
				return (0);
		}
		else if (!ps_operand(ps, RA, 1))
			return (0);
		if (is_it_indexed(ps, 'a'))
			return (1);
	}
	return (1);
}

/*size_t		find_best_insertion(t_pushswap *ps)
{
	int	ra;
	int	rb;
	int rra;
	int rrb;
	t_stack *elem;
	t_stack	*tmp;

	elem = ps->top_b;
	rb = 0;
	rrb = ps->b;
	while (elem)
	{
		if (elem->index < find_min('a', ps))
		{
			tmp = find_elem('a', ps, find_min('a', ps));
			//find distance to top
		}
		else if (elem->index > find_max('a', ps))
		{
			tmp = find_elem('a', ps, find_max('a', ps));
			//find distance to top
		}
		else
		{
			tmp = ps->top_a;
			while (tmp)
			{
				if (tmp == ps->top_a)
				{
					if (tmp->index > elem->index && ps->bot_a->index < elem->index)
						//immediate push
					tmp = tmp->prev;
				}
				else
				{
					if (tmp->index > elem->index && tmp->prev->index < elem->index)
					{
						//find distance to top
					}
				}
			}
		}
	}
}

int			sort_b(t_pushswap *ps)
{
	size_t	index;

	while (ps->b)
	{
		index = find_best_insertion(ps);
	}
}i*/

int			sort_by_step(t_pushswap *ps, size_t (*mode)(t_pushswap *, size_t))
{
	t_stack	*elem;
	size_t	i;

	find_index(ps);
	elem = ps->top_a;
	while (elem)
	{
		elem->val = 0;
		elem = elem->prev;
	}
	i = find_best_index(ps, mode);
	sort_a(ps, i, mode);
	/*sort_b(ps);
	align(ps);*/
	return (1);
}
