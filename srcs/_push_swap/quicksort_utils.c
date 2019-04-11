/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:18:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:18:35 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

int	backtrack_stack(int option, t_pushswap *ps, size_t rr)
{
	size_t	c;
	int		r1;
	int		r2;

	c = (option == 'a') ? ps->a : ps->b;
	r1 = (option == 'a') ? RA : RB;
	r2 = (option == 'a') ? RRA : RRB;
	if (rr > c / 2)
	{
		while (c - rr++)
			if (!ps_operand(ps, r1, 1))
				return (0);
	}
	else
	{
		while (rr--)
			if (!ps_operand(ps, r2, 1))
				return (0);
	}
	return (1);
}

int	other_push_needed(int option, t_pushswap *ps, size_t len, int pivot)
{
	t_stack	*elem;

	elem = option == 'a' ? ps->top_a : ps->top_b;
	while (len--)
	{
		if ((option == 'a' && elem->val < pivot)
			|| (option == 'b' && elem->val > pivot))
			return (1);
		elem = elem->prev;
	}
	return (0);
}
