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

void		find_distance(t_pushswap *ps, t_stack *tmp, size_t *ra, size_t *rra)
{
	t_stack	*elem;

	*ra = 0;
	*rra = ps->a;
	elem = ps->top_a;
	while (elem != tmp)
	{
		(*ra)++;
		(*rra)--;
		elem = elem->prev;
	}
}

int	ft_abs(t_move *mov, size_t size, size_t index)
{
	size_t	prev;
	size_t	new;

	prev = mov->i > size / 2 ? mov->i - size / 2 : size / 2 - mov->i;
	new = index > size / 2 ? index - size / 2 : size / 2 - index;
	if (prev > new)
	{
		mov->i = index;
		return (1);
	}
	return (0);
}

size_t			ft_best(size_t ra, size_t rb, size_t rra, size_t rrb, t_move *mov, size_t size, size_t index)
{
	size_t	rr;
	size_t rrr;
	size_t rab;
	size_t rba;

	rr = ra < rb ? rb : ra;
	rrr = rra < rrb ? rrb : rra;
	rab = ra + rrb;
	rba = rb + rra;
	if (rr <= rrr && rr <= rab && rr <= rba)
	{
		if (mov->real > rr || (mov->real == rr && ft_abs(mov, size, index)))
		{
			mov->real = rr;
			mov->rra = 0;
			mov->rrb = 0;
			mov->ra = ra;
			mov->rb = rb;
		}
		return (rr);
	}
	if (rrr <= rr && rrr <= rab && rrr <= rba)
	{
		if (mov->real > rrr || (mov->real == rrr && ft_abs(mov, size, index)))
		{
			mov->real = rrr;
			mov->rra = rra;
			mov->rrb = rrb;
			mov->ra = 0;
			mov->rb = 0;
		}
		return (rrr);
	}
	if (rab <= rrr && rab <= rrr && rab <= rba)
	{
		if (mov->real > rab || (mov->real == rab && ft_abs(mov, size, index)))
		{
			mov->real = rab;
			mov->rra = 0;
			mov->rrb = rrb;
			mov->ra = ra;
			mov->rb = 0;
		}
		return (rab);
	}
	if (mov->real > rba || (mov->real == rba && ft_abs(mov, size, index)))
	{
		mov->real = rba;
		mov->rra = rra;
		mov->rrb = 0;
		mov->ra = 0;
		mov->rb = rb;
	}
	return (rba);
}

size_t		find_best_insertion(t_pushswap *ps, t_stack **mem_a, t_stack **mem_b, t_move *mov)
{
	size_t	ra;
	size_t	rb;
	size_t	rra;
	size_t	rrb;
	size_t	mem;
	t_stack *elem;
	t_stack	*tmp;

	mem = LONG_MAX;
	elem = ps->top_b;
	rb = 0;
	rrb = ps->b;
	while (elem)
	{
		if (elem->index < find_min('a', ps) || elem->index > find_max('a', ps))
		{
			tmp = find_elem('a', ps, find_min('a', ps));
			find_distance(ps, tmp, &ra, &rra);
		}
		else
		{
			tmp = ps->top_a;
			while (tmp)
			{
				if (tmp == ps->top_a)
				{
					if (tmp->index > elem->index && ps->bot_a->index < elem->index)
					{
						find_distance(ps, tmp, &ra, &rra);
						break ;
					}
				}
				else if (tmp->index > elem->index && tmp->next->index < elem->index)
				{
					find_distance(ps, tmp, &ra, &rra);
					break ;
				}
					tmp = tmp->prev;
			}
		}
		ra = ft_best(ra, rb, rra, rrb, mov, ps->a + ps->b, tmp->index);
		if (mem > ra)
		{
			*mem_a = tmp;
			*mem_b = elem;
			mem = ra;
			mov->real = ra;
		}
		rb++;
		rrb--;
		elem = elem->prev;
	}
	return (0);
}

int			sort_b(t_pushswap *ps)
{
	size_t	index;
	t_stack *mem_a;
	t_stack *mem_b;
	t_move	mov;

	while (ps->b)
	{
		mem_a = 0;
		mem_b = 0;
		ft_bzero(&mov, sizeof(mov));
		mov.real = LONG_MAX;
		index = find_best_insertion(ps, &mem_a, &mem_b, &mov);
		(void)index;
		while (mov.ra--)
			if (!ps_operand(ps, RA, 1))
				return (0);
		while (mov.rb--)
			if (!ps_operand(ps, RB, 1))
				return (0);
		while (mov.rra--)
			if (!ps_operand(ps, RRA, 1))
				return (0);
		while (mov.rrb--)
			if (!ps_operand(ps, RRB, 1))
				return (0);
		if (!ps_operand(ps, PA, 1))
				return (0);
	}
	return (0);
}

int		align_a(t_pushswap *ps)
{
	t_stack *elem;
	t_stack *tmp;
	size_t		ra;
	size_t		rra;
	int			op;

	elem = ps->top_a;
	tmp = find_elem('a', ps, find_min('a', ps));
	ra = 0;
	rra = ps->a;
	while (elem != tmp)
	{
		elem = elem->prev;
		ra++;
		rra--;
	}
	op = (ra <= rra) ? RA : RRA;
	ra = (ra <= rra) ? ra : rra;
	while (ra--)
		if (!ps_operand(ps, op, 1))
			return (0);
	return (1);
}

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
	sort_b(ps);
	align_a(ps);
	return (1);
}
