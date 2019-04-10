/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:31:30 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 12:32:17 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

static inline int		align(t_pushswap *ps)
{
	t_stack	*elem;
	t_stack	*tmp;
	size_t	ra;
	size_t	rra;
	int		op;

	elem = ps->top_a;
	tmp = find_elem_index('a', ps, find_min_index('a', ps));
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

static inline size_t		find_best_index(t_pushswap *ps, int *err,
							size_t (*mode)(t_pushswap *, size_t))
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
		if (!ps_operand(ps, RA, 1))
			return (0);
	}
	*err = 0;
	stackdel(&ps->instruction_begin);
	mode(ps, best->index);
	return (best->index);
}

int			sort_by_step(t_pushswap *ps, size_t (*mode)(t_pushswap *, size_t))
{
	t_stack	*elem;
	size_t	i;
	int		err;

	if (!define_index(ps))
		return (0);
	elem = ps->top_a;
	while (elem)
	{
		elem->val = 0;
		elem = elem->prev;
	}
	err = 1;
	i = find_best_index(ps, &err,mode);
	if (err)
		return (0);
	sort_step1(ps, i, mode);
	sort_step2(ps);
	align(ps);
	return (1);
}
