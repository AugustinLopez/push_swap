/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_step2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:29:47 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:17:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

static inline t_stack	*find_move_a(t_pushswap *ps, t_stack *tmp,
										size_t *ra, size_t *rra)
{
	t_stack	*elem;

	*ra = 0;
	*rra = ps->a;
	elem = ps->top_a;
	while (elem != tmp)
	{
		(*ra)++;
		(*rra)--;
		elem = elem->prev;
	}
	return (tmp);
}

static inline t_stack	*find_place_in_a(t_pushswap *ps, t_stack *elem,
										t_move *foo)
{
	t_stack *tmp;

	if (elem->index < find_min_index('a', ps)
		|| elem->index > find_max_index('a', ps))
	{
		tmp = find_elem_index('a', ps, find_min_index('a', ps));
		return (find_move_a(ps, tmp, &(foo->ra), &(foo->rra)));
	}
	tmp = ps->top_a;
	while (tmp)
	{
		if (tmp == ps->top_a
			&& tmp->index > elem->index && ps->bot_a->index < elem->index)
			return (find_move_a(ps, tmp, &(foo->ra), &(foo->rra)));
		else if (tmp != ps->top_a
			&& tmp->index > elem->index && tmp->next->index < elem->index)
			return (find_move_a(ps, tmp, &(foo->ra), &(foo->rra)));
		tmp = tmp->prev;
	}
	return (tmp);
}

static inline void		find_best_insertion(t_pushswap *ps, t_stack **mem_a,
								t_stack **mem_b, t_move *rrx)
{
	t_move	foo;
	t_stack *elem;
	t_stack	*tmp;
	size_t	bar;

	ft_bzero(&foo, sizeof(foo));
	foo.real = LONG_MAX;
	foo.rrb = ps->b;
	elem = ps->top_b;
	while (elem)
	{
		tmp = find_place_in_a(ps, elem, &foo);
		bar = nbr_move_to_a(&foo, rrx, ps->a + ps->b, tmp->index);
		if (bar < foo.real)
		{
			*mem_a = tmp;
			*mem_b = elem;
			foo.real = bar;
		}
		foo.rb++;
		foo.rrb--;
		elem = elem->prev;
	}
}

static inline int		perform_oper(t_pushswap *ps, t_move *rrx)
{
	while (rrx->ra--)
		if (!ps_operand(ps, RA, 1))
			return (0);
	while (rrx->rb--)
		if (!ps_operand(ps, RB, 1))
			return (0);
	while (rrx->rra--)
		if (!ps_operand(ps, RRA, 1))
			return (0);
	while (rrx->rrb--)
		if (!ps_operand(ps, RRB, 1))
			return (0);
	if (!ps_operand(ps, PA, 1))
		return (0);
	return (1);
}

int						sort_step2(t_pushswap *ps)
{
	t_stack *mem_a;
	t_stack *mem_b;
	t_move	rrx;

	while (ps->b)
	{
		mem_a = 0;
		mem_b = 0;
		ft_bzero(&rrx, sizeof(rrx));
		rrx.real = LONG_MAX;
		find_best_insertion(ps, &mem_a, &mem_b, &rrx);
		if (!perform_oper(ps, &rrx))
			return (1);
	}
	return (0);
}
