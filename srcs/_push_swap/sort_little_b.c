/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_only_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:17:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 11:04:03 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	sort3(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	z = (len == 3) ? ps->top_b->prev->prev->val : 0;
	if (x < y && y < z)
		return (ps_operand(ps, SB, 1) && ps_operand(ps, RRB, 1));
	else if (y < z && z < x)
		return (ps_operand(ps, RRB, 1) && ps_operand(ps, SB, 1));
	else if (y < x && x < z)
		return (ps_operand(ps, RRB, 1));
	else if (x < z && z < y)
		return (ps_operand(ps, RB, 1));
	else if (z < x && x < y)
		return (ps_operand(ps, SB, 1));
	return (1);
}

inline static int	sort3_notonplace(t_pushswap *ps, size_t len)
{
	while (--len)
	{
		if (ps->top_b->val < ps->top_b->prev->val)
		{
			if (!ps_operand(ps, SB, 1) || !ps_operand(ps, RB, 1))
				return (0);
		}
		else if (!ps_operand(ps, RB, 1))
			return (0);
	}
	while (++len < 3)
	{
		if (!ps_operand(ps, RRB, 1))
			return (0);
		if (ps->top_b->val < ps->top_b->prev->val)
			if (!ps_operand(ps, SB, 1))
				return (0);
	}
	if (ps->top_b && ps->top_b->val < ps->top_b->prev->val)
		if (!ps_operand(ps, SB, 1))
			return (0);
	return (1);
}

int					sort_little_b(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	if (len == 1)
		return (1);
	else if (len == 2 && x < y)
		return (ps_operand(ps, SB, 1));
	else if (ps->b == 3 && len == 3)
		return (sort3(ps, len));
	else if (len == 3)
		return (sort3_notonplace(ps, len));
	return (1);
}
