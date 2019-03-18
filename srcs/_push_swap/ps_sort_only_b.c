/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_only_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:17:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 18:56:48 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

//memory need to be monitored. ps_operand should return 0 or -1

int		sort_onplace_b(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	z = (len == 3) ? ps->top_b->prev->prev->val : 0;
	if (x < y && y < z)
	{
		ps_operand(ps, SB, 1);
		ps_operand(ps, RRB, 1);
	}
	else if (y < z && z < x)
	{
		ps_operand(ps, RRB, 1);
		ps_operand(ps, SB, 1);
	}
	else if (y < x && x < z)
		ps_operand(ps, RRB, 1);
	else if (x < z && z < y) 
		ps_operand(ps, RB, 1);
	else if (z < x && x < y)
		ps_operand(ps, SB, 1);
	return (0);
}

int		sort_notonplace_b(t_pushswap *ps, size_t len)
{
	while (--len)
	{
		if (ps->top_b->val < ps->top_b->prev->val)
		{
			ps_operand(ps, SB, 1);
			ps_operand(ps, RB, 1);
		}
		else
			ps_operand(ps, RB, 1);
	}
	while (++len < 3)
	{
		ps_operand(ps, RRB, 1);
		if (ps->top_b->val < ps->top_b->prev->val)
			ps_operand(ps, SB, 1);
	}
	if (ps->top_b && ps->top_b->val < ps->top_b->prev->val)
		ps_operand(ps, SB, 1);
	return (0);
}

inline static int		sort_onplace_4b2(int x, int y, int z, int v)
{
	if (y < z && z < x && x < v)
		return (RB + SB * 10 + RB * 100 + RB * 1000);
	else if (y < v && v < x && x < z)
		return (RRB + SB * 10 + RRB * 100);
	else if (z < y && y < x && x < v)
		return (RRB);
	else if (v < y && y < x && x < z)
		return (PA + SB * 10 + PB * 100 + SB * 1000);
	else if (z < v && v < x && x < y)
		return (PA + PA * 10 + SS * 100 + PB * 1000 + PB * 10000);
	else if (v < z && z < x && x < y)
		return (SB);
	else if (y < z && z < v && v < x)
		return (PA + RB * 10 + SB * 100 + PB * 1000);
	else if (y < v && v < z && z < x)
		return (SB + RB * 10);
	else if (z < y && y < v && v < x)
		return (RRB + SB * 10);
	else if (v < y && y < z && z < x)
		return (PA + SB * 10 + PB * 100);
	else if (z < v && v < y && y < x)
		return (RB + RB * 10 + SB * 100 + RB * 1000 + RB * 10000);
	return (0);
}

inline static int		sort_onplace_4b(int x, int y, int z, int v)
{
	if (x < y && y < z && z < v)
		return (SB + RB * 10 + RB * 100 + SB * 1000);
	else if (x < y && y < v && v < z)
		return (SB + RB * 10 + RB * 100);
	else if (x < z && z < y && y < v)
		return (RRB + SB * 10 + RB * 100);
	else if (x < z && z < v && v < y)
		return (RB + PA * 10 + SB * 100 + PB * 1000);
	else if (x < v && v < z && z < y)
		return (RB);
	else if (x < v && v < y && y < z)
		return (RB + SB * 10);
	else if (y < x && x < z && z < v)
		return (RRB + RRB * 10 + SB * 100);
	else if (y < x && x < v && v < z)
		return (RB + RB * 10);
	else if (z < x && x < y && y < v)
		return (SB + RRB * 10);
	else if (v < x && x < y && y < z)
		return (RRB + SB * 10 + RB * 100 + RB * 1000 + SB * 10000);
	else if (z < x && x < v && v < y)
		return (RB + PA * 10 + RB * 100 + PB * 1000);
	else if (v < x && x < z && z < y)
		return (RRB + SB * 10 + RB * 100 + RB * 1000);
	return (sort_onplace_4b2(x, y, z, v));
}

int		sort_little_b(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;
	int	v;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	z = (len >= 3) ? ps->top_b->prev->prev->val : 0;
	v = (len == 4) ? ps->top_b->prev->prev->prev->val : 0;
	if (len == 1)
		return (0);
	else if (len == 2 && x < y)
		ps_operand(ps, SB, 1);
	else if (ps->b == 3 && len == 3)
		sort_onplace_b(ps, len);
	else if (len == 3)
		sort_notonplace_b(ps, len);
	else if (len == 4)
		ps_several_operand(ps, sort_onplace_4b(x, y, z, v));
	return (0);
}
