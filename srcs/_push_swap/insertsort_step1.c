/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_step1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:53:16 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 12:07:27 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

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

static inline int	needs_sa(t_pushswap *ps, size_t best,
								size_t (*mode)(t_pushswap *, size_t))
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

static inline int	is_it_done(t_pushswap *ps, int option)
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

int			sort_step1(t_pushswap *ps, size_t best_index,
					size_t (*mode)(t_pushswap *, size_t))
{
	int	i;

	while (needs_pb(ps))
	{
		if ((i = needs_sa(ps, best_index, mode)))
		{
			if (i == -1 || !ps_operand(ps, SA, 1))
				return (0);
			mode(ps, best_index);
		}
		else if (ps->top_a->val == 0)
		{
			if (!ps_operand(ps, PB, 1))
				return (0);
		}
		else if (!ps_operand(ps, RA, 1))
			return (0);
		if (is_it_done(ps, 'a'))
			return (1);
	}
	return (1);
}
