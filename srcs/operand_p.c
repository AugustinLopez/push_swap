/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:35:35 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:16:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static void	push_b(t_pushswap *ps)
{
	t_stack	*tmp;

	tmp = ps->top_a->prev;
	ps->top_a->prev = ps->top_b;
	if (tmp)
		tmp->next = NULL;
	else
		ps->bot_a = NULL;
	if (ps->top_b)
	{
		ps->top_b->next = ps->top_a;
		ps->top_b = ps->top_b->next;
	}
	else
	{
		ps->top_b = ps->top_a;
		ps->bot_b = ps->top_a;
	}
	ps->top_a = tmp;
}

inline static void	push_a(t_pushswap *ps)
{
	t_stack	*tmp;

	tmp = ps->top_b->prev;
	ps->top_b->prev = ps->top_a;
	if (tmp)
		tmp->next = NULL;
	else
		ps->bot_b = NULL;
	if (ps->top_a)
	{
		ps->top_a->next = ps->top_b;
		ps->top_b->prev = ps->top_a;
		ps->top_a = ps->top_a->next;
	}
	else
	{
		ps->top_a = ps->top_b;
		ps->bot_a = ps->top_b;
	}
	ps->top_b = tmp;
}

void				ps_push(t_pushswap *ps, int option)
{
	if (option == PA && ps->top_b)
	{
		push_a(ps);
		(ps->a)++;
		(ps->b)--;
	}
	else if (option == PB && ps->top_a)
	{
		push_b(ps);
		(ps->b)++;
		(ps->a)--;
	}
}
