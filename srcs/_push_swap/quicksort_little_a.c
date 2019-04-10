/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_only_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:40:01 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 11:03:01 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	sort3(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;

	x = ps->top_a->val;
	y = (len >= 2) ? ps->top_a->prev->val : 0;
	z = (len == 3) ? ps->top_a->prev->prev->val : 0;
	if (x > y && y > z)
		return (ps_operand(ps, SA, 1) && ps_operand(ps, RRA, 1));
	else if (y > z && z > x)
		return (ps_operand(ps, RRA, 1) && ps_operand(ps, SA, 1));
	else if (y > x && x > z)
		return (ps_operand(ps, RRA, 1));
	else if (x > z && z > y)
		return (ps_operand(ps, RA, 1));
	else if (z > x && x > y)
		return (ps_operand(ps, SA, 1));
	return (1);
}

inline static int	sort3_notonplace(t_pushswap *ps, size_t len)
{
	while (--len)
	{
		if (ps->top_a->val > ps->top_a->prev->val)
		{
			if (!ps_operand(ps, SA, 1) || !ps_operand(ps, RA, 1))
				return (0);
		}
		else if (!ps_operand(ps, RA, 1))
			return (0);
	}
	while (++len < 3)
	{
		if (!ps_operand(ps, RRA, 1))
			return (0);
		if (ps->top_a && ps->top_a->val > ps->top_a->prev->val)
			if (!ps_operand(ps, SA, 1))
				return (0);
	}
	if (ps->top_a && ps->top_a->val > ps->top_a->prev->val)
		if (!ps_operand(ps, SA, 1))
			return (0);
	return (1);
}

inline static int	sort4_bis(int x, int y, int z, int v)
{
	if (y > z && z > x && x > v)
		return (RA + SA * 10 + RA * 100 + RA * 1000);
	else if (y > v && v > x && x > z)
		return (RRA + SA * 10 + RRA * 100);
	else if (z > y && y > x && x > v)
		return (RRA);
	else if (v > y && y > x && x > z)
		return (PB + SA * 10 + PA * 100 + SA * 1000);
	else if (z > v && v > x && x > y)
		return (PB + PB * 10 + SS * 100 + PA * 1000 + PA * 10000);
	else if (v > z && z > x && x > y)
		return (SA);
	else if (y > z && z > v && v > x)
		return (PB + RA * 10 + SA * 100 + PA * 1000);
	else if (y > v && v > z && z > x)
		return (SA + RA * 10);
	else if (z > y && y > v && v > x)
		return (RRA + SA * 10);
	else if (v > y && y > z && z > x)
		return (PB + SA * 10 + PA * 100);
	else if (z > v && v > y && y > x)
		return (RA + RA * 10 + SA * 100 + RA * 1000 + RA * 10000);
	return (0);
}

inline static int	sort4(int x, int y, int z, int v)
{
	if (x > y && y > z && z > v)
		return (SA + RA * 10 + RA * 100 + SA * 1000);
	else if (x > y && y > v && v > z)
		return (SA + RA * 10 + RA * 100);
	else if (x > z && z > y && y > v)
		return (RRA + SA * 10 + RA * 100);
	else if (x > z && z > v && v > y)
		return (RA + PB * 10 + SA * 100 + PA * 1000);
	else if (x > v && v > z && z > y)
		return (RA);
	else if (x > v && v > y && y > z)
		return (RA + SA * 10);
	else if (y > x && x > z && z > v)
		return (RRA + RRA * 10 + SA * 100);
	else if (y > x && x > v && v > z)
		return (RA + RA * 10);
	else if (z > x && x > y && y > v)
		return (SA + RRA * 10);
	else if (v > x && x > y && y > z)
		return (RRA + SA * 10 + RA * 100 + RA * 1000 + SA * 10000);
	else if (z > x && x > v && v > y)
		return (RA + PB * 10 + RA * 100 + PA * 1000);
	else if (v > x && x > z && z > y)
		return (RRA + SA * 10 + RA * 100 + RA * 1000);
	return (sort4_bis(x, y, z, v));
}

int					sort_little_a(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;
	int	v;

	x = ps->top_a->val;
	y = (len >= 2) ? ps->top_a->prev->val : 0;
	z = (len >= 3) ? ps->top_a->prev->prev->val : 0;
	v = (len == 4) ? ps->top_a->prev->prev->prev->val : 0;
	if (len == 1)
		return (1);
	else if (len == 2 && x > y)
		return (ps_operand(ps, SA, 1));
	else if (ps->a == 3 && len == 3)
		return (sort3(ps, len));
	else if (len == 3)
		return (sort3_notonplace(ps, len));
	else if (ps->a == 4 && len == 4)
		return (ps_several_operand(ps, sort4(x, y, z, v)));
	return (1);
}
