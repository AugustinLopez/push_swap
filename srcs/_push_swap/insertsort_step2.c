/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_step2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 12:29:47 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 13:35:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

t_stack		*find_move_a(t_pushswap *ps, t_stack *tmp, size_t *ra, size_t *rra)
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

int	ft_abs(t_move *cur, size_t size, size_t index)
{
	size_t	prev;
	size_t	new;

	prev = cur->i > size / 2 ? cur->i - size / 2 : size / 2 - cur->i;
	new = index > size / 2 ? index - size / 2 : size / 2 - index;
	if (prev > new)
	{
		cur->i = index;
		return (4);
	}
	return (0);
}

static inline size_t	calc(int option, t_move *cur, size_t r1, size_t r2)
{
	size_t	real;
	int		case_equal;

	case_equal = 0;
	if (option > 4)
	{
		option -= 4;
		case_equal = 1;
	}
	if (option == 1 || option == 2)
		real = (r1 < r2) ? r2 : r1;
	else
		real = r1 + r2;
	if (cur->real > real || (cur->real == real && case_equal))
	{
		cur->real = real;
		cur->rra = (option == 2 || option == 4) * r1;
		cur->rrb = (option == 2 || option == 3) * r2;
		cur->ra = (option == 1 || option == 3) * r1;
		cur->rb = (option == 1 || option == 4) * r2;
	}
	return (real);
}

size_t			ft_best(t_move *temp, t_move *cur, size_t size, size_t index)
{
	size_t	rr;
	size_t rrr;
	size_t rab;
	size_t rba;

	rr = temp->ra < temp->rb ? temp->rb : temp->ra;
	rrr = temp->rra < temp->rrb ? temp->rrb : temp->rra;
	rab = temp->ra + temp->rrb;
	rba = temp->rra + temp->rb;
	if (rr <= rrr && rr <= rab && rr <= rba)
		return (calc(1 + ft_abs(cur, size, index), cur, temp->ra, temp->rb));
	else if (rrr <= rr && rrr <= rab && rrr <= rba)
		return (calc(2 + ft_abs(cur, size, index), cur, temp->rra, temp->rrb));
	else if (rab <= rrr && rab <= rrr && rab <= rba)
		return (calc(3 + ft_abs(cur, size, index), cur, temp->ra, temp->rrb));
	return (calc(4 + ft_abs(cur, size, index), cur, temp->rra, temp->rb));
}

t_stack		*best_loop(t_pushswap *ps, t_stack *elem, t_move *cal)
{
	t_stack *tmp;

	if (elem->index < find_min_index('a', ps)
		|| elem->index > find_max_index('a', ps))
	{
		tmp = find_elem_index('a', ps, find_min_index('a', ps));
		return (find_move_a(ps, tmp, &(cal->ra), &(cal->rra)));
	}
	tmp = ps->top_a;
	while (tmp)
	{
		if (tmp == ps->top_a
			&& tmp->index > elem->index && ps->bot_a->index < elem->index)
			return (find_move_a(ps, tmp, &(cal->ra), &(cal->rra)));
		else if (tmp != ps->top_a
			&& tmp->index > elem->index && tmp->next->index < elem->index)
			return (find_move_a(ps, tmp, &(cal->ra), &(cal->rra)));
		tmp = tmp->prev;
	}
	return (tmp);
}

size_t		find_best_insertion(t_pushswap *ps, t_stack **mem_a,
								t_stack **mem_b, t_move *cur)
{
	t_move	cal;
	t_stack *elem;
	t_stack	*tmp;

	ft_bzero(&cal, sizeof(cal));
	cal.real = LONG_MAX;
	cal.rrb = ps->b;
	elem = ps->top_b;
	while (elem)
	{
		tmp = best_loop(ps, elem, &cal);
		cal.ra = ft_best(&cal, cur, ps->a + ps->b, tmp->index);
		if (cal.real > cal.ra)
		{
			*mem_a = tmp;
			*mem_b = elem;
			cal.real = cal.ra;
		}
		cal.rb++;
		cal.rrb--;
		elem = elem->prev;
	}
	return (0);
}

int			perform_oper(t_pushswap *ps, t_move *cur)
{
	while (cur->ra--)
		if (!ps_operand(ps, RA, 1))
			return (0);
	while (cur->rb--)
		if (!ps_operand(ps, RB, 1))
			return (0);
	while (cur->rra--)
		if (!ps_operand(ps, RRA, 1))
			return (0);
	while (cur->rrb--)
		if (!ps_operand(ps, RRB, 1))
			return (0);
	if (!ps_operand(ps, PA, 1))
			return (0);
	return (1);
}

int			sort_step2(t_pushswap *ps)
{
	size_t	index;
	t_stack *mem_a;
	t_stack *mem_b;
	t_move	cur;

	while (ps->b)
	{
		mem_a = 0;
		mem_b = 0;
		ft_bzero(&cur, sizeof(cur));
		cur.real = LONG_MAX;
		index = find_best_insertion(ps, &mem_a, &mem_b, &cur);
		(void)index;
		(void)perform_oper(ps, &cur);
	}
	return (0);
}
