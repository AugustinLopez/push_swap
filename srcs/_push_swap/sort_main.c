/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 11:02:41 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 11:02:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	loop_quicksort_b(t_pushswap *ps, int pivot,
									size_t *rb, size_t *pa)
{
	if (ps->top_b->val > pivot && ++(*pa))
	{
		if (!ps_operand(ps, PA, 1))
			return (0);
	}
	else if (++(*rb) && !ps_operand(ps, RB, 1))
		return (0);
	return (1);
}

inline static int	sort_stack_b(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	rb;
	size_t	pa;
	size_t	i;

	rb = 0;
	pa = 0;
	i = 0;
	if (len <= 3)
		return (sort_little_b(ps, len));
	if (!(pivot = get_pivot('b', ps, len, &i)) && i)
		return (0);
	while (other_push_needed('b', ps, len - i, pivot) && i++ < len)
		if (!loop_quicksort_b(ps, pivot, &rb, &pa))
			return (0);
	if (!sort_stack_a(ps, pa)
		|| !backtrack_stack('b', ps, rb)
		|| !sort_stack_b(ps, len - pa))
		return (0);
	while (ps->a && pa--)
		if (!ps_operand(ps, PB, 1))
			return (0);
	return (1);
}

inline static int	loop_quicksort_a(t_pushswap *ps, int pivot,
									size_t *ra, size_t *pb)
{
	if (ps->top_a->val < pivot && ++(*pb))
	{
		if (!ps_operand(ps, PB, 1))
			return (0);
	}
	else if (++(*ra) && !ps_operand(ps, RA, 1))
		return (0);
	return (1);
}

int					sort_stack_a(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	ra;
	size_t	pb;
	size_t	i;

	i = 0;
	ra = 0;
	pb = 0;
	if (len <= 3 || (len == 4 && ps->a == 4))
		return (sort_little_a(ps, len));
	if (!(pivot = get_pivot('a', ps, len, &i)) && i)
		return (0);
	while (other_push_needed('a', ps, len - i, pivot) && i++ < len)
		if (!loop_quicksort_a(ps, pivot, &ra, &pb))
			return (0);
	if (!backtrack_stack('a', ps, ra)
		|| !sort_stack_a(ps, len - pb)
		|| !sort_stack_b(ps, pb))
		return (0);
	while (ps->b && pb--)
		if (!ps_operand(ps, PA, 1))
			return (0);
	return (1);
}
