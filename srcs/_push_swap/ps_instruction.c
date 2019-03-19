/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instruction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:46:12 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/19 15:20:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	simple_free(t_stack **oper, t_stack **elem, t_stack **tmp)
{
	!((*elem)->prev) ? (*oper) = (*elem)->next : 0;
	if ((*oper) == (*tmp))
		(*oper) = (*tmp)->next;
	stackdelone(elem);
	stackdelone(tmp);
	return (1);
}

inline static int	squash_simple(t_pushswap *ps, int opt1, int opt2, int jump)
{
	t_stack	*elem;
	t_stack	*tmp;
	int		loop;

	loop = 0;
	elem = ps->instruction_begin;
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->val == opt1)
		{
			tmp = elem->next;
			while (tmp && tmp->val == jump)
				tmp = tmp->next;
			if (tmp && tmp->val == opt2)
				loop = simple_free(&(ps->instruction_begin), &elem, &tmp);
		}
		elem = (elem != 0) ? elem->next : 0;
	}
	return (loop);
}

static inline void	r_free(t_stack **first, t_stack **elem, int opt1, int opt3)
{
	(*first)->val = opt3;
	stackdelone(elem);
	if ((*first)->next && (*first)->next->val == opt1)
		(*first) = (*first)->next;
	else
		(*first) = 0;
}

inline static int	squash_r(t_pushswap *ps, int opt1, int opt2, int jump)
{
	t_stack	*elem;
	t_stack	*first;
	int		loop;
	int		opt3;

	opt3 = SS * (opt1 == SA || opt2 == SA);
	opt3 += RR * (opt1 == RA || opt2 == RA);
	opt3 += RRR * (opt1 == RRA || opt2 == RRA);
	loop = 0;
	elem = ps->instruction_begin;
	first = 0;
	while (elem)
	{
		if (!elem->next)
			break ;
		else if (!first && elem->val == opt1)
			first = elem;
		else if (first && elem->val == opt2)
			r_free(&first, &elem, opt1, opt3);
		else if (elem->val != jump)
			first = 0;
		elem = elem->next;
	}
	return (loop);
}

int					squash_operand_stack(t_pushswap *ps)
{
	int		loop;
	t_stack	*elem;

	loop = 1;
	elem = ps->instruction_begin;
	if (!elem)
		return (0);
	while (loop)
	{
		loop = squash_simple(ps, SA, SA, RB) + squash_simple(ps, SB, SB, RA);
		loop += squash_simple(ps, SA, SA, RRB) + squash_simple(ps, SB, SB, RRA);
		loop += squash_simple(ps, RA, RRA, SB) + squash_simple(ps, RB, RRB, SA);
		loop += squash_simple(ps, RRA, RA, SB) + squash_simple(ps, RRB, RB, SA);
		loop += squash_simple(ps, PA, PB, 0) + squash_simple(ps, PB, PA, 0);
	}
	loop = 1;
	while (loop)
	{
		loop = squash_r(ps, SA, SB, RA) + squash_r(ps, SB, SA, RB);
		loop += squash_r(ps, SA, SB, RRA) + squash_r(ps, SB, SA, RRB);
		loop += squash_r(ps, RA, RB, SA) + squash_r(ps, RB, RA, SB);
		loop += squash_r(ps, RRA, RRB, SA) + squash_r(ps, RRB, RRA, SB);
	}
	return (0);
}
