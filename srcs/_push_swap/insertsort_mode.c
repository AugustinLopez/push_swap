/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:03:36 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 12:03:46 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

size_t		mode_incremental(t_pushswap *ps, size_t index)
{
	size_t	i;
	t_stack	*elem;
	t_stack *best;
	size_t	mem;

	if (!ps->a)
		return (0);
	best = find_elem_index('a', ps, index);
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
	best = find_elem_index('a', ps, index);
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
