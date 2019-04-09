/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_squash_instruction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:45:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 12:44:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	squash_rfree(t_stack **oper, t_stack **elem, t_stack **tmp)
{
	!((*elem)->prev) ? (*oper) = (*elem)->next : 0;
	if ((*oper) == (*tmp))
		(*oper) = (*tmp)->next;
	stackdelone(elem);
	stackdelone(tmp);
	return (1);
}

inline static int	squash_remove(t_pushswap *ps, int opt1, int opt2, int jump)
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
				loop = squash_rfree(&(ps->instruction_begin), &elem, &tmp);
		}
		elem = (elem != 0) ? elem->next : 0;
	}
	return (loop);
}

static inline int	squash_cfree(t_stack **tmp, t_stack **elem, int o1, int o3)
{
	(*tmp)->val = o3;
	stackdelone(elem);
	if ((*tmp)->next && (*tmp)->next->val == o1)
		(*tmp) = (*tmp)->next;
	else
		(*tmp) = 0;
	return (1);
}

inline static int	squash_combi(t_pushswap *ps, int opt1, int opt2, int jump)
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
		{
			loop = squash_cfree(&first, &elem, opt1, opt3);
			elem = first;
			first = 0;
			continue ;
		}
		else if (elem->val != jump && elem->val != opt3 && elem->val != opt1)
			first = 0;
		elem = (elem != 0) ? elem->next : 0;
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
		loop = squash_remove(ps, SA, SA, RB) + squash_remove(ps, SB, SB, RA);
		loop += squash_remove(ps, SA, SA, RRB) + squash_remove(ps, SB, SB, RRA);
		loop += squash_remove(ps, RA, RRA, SB) + squash_remove(ps, RB, RRB, SA);
		loop += squash_remove(ps, RRA, RA, SB) + squash_remove(ps, RRB, RB, SA);
		loop += squash_remove(ps, PA, PB, 0) + squash_remove(ps, PB, PA, 0);
	}
	loop = 1;
	while (loop)
	{
		loop = squash_combi(ps, SA, SB, RA) + squash_combi(ps, SB, SA, RB);
		loop += squash_combi(ps, SA, SB, RRA) + squash_combi(ps, SB, SA, RRB);
		loop += squash_combi(ps, RA, RB, SA) + squash_combi(ps, RB, RA, SB);
		loop += squash_combi(ps, RRA, RRB, SA) + squash_combi(ps, RRB, RRA, SB);
	}
	return (0);
}
