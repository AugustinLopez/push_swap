/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:30:26 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/19 14:41:59 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

int					load_operand_stack(t_pushswap *ps, int instruction)
{
	t_stack	*elem;

	if (!(ps->instruction_begin))
	{
		if (!(ps->instruction_begin = ft_memalloc(sizeof(t_stack))))
			return (0);
		ps->instruction_begin->val = instruction;
		ps->instruction_end = ps->instruction_begin;
	}
	else
	{
		if (!(elem = ft_memalloc(sizeof(t_stack))))
			return (0);
		elem->val = instruction;
		elem->prev = ps->instruction_end;
		ps->instruction_end->next = elem;
		ps->instruction_end = elem;
	}
	return (1);
}

int					ps_several_operand(t_pushswap *ps, int option)
{
	while (option)
	{
		if (!(ps_operand(ps, option % 10, 1)))
			return (0);
		option /= 10;
	}
	return (1);
}

int					ps_operand(t_pushswap *ps, int option, int affichage)
{
	if (option == SA || option == SB || option == SS)
		ps_swap(ps, option);
	else if (option == PA || option == PB)
		ps_push(ps, option);
	else if (option == RA || option == RB || option == RR)
		ps_rotate(ps, option);
	else if (option == RRA || option == RRB || option == RRR)
		ps_reverse_rotate(ps, option);
	if (affichage)
		return (load_operand_stack(ps, option));
	return (1);
}
