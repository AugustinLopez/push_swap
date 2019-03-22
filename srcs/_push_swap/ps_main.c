/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/22 18:14:23 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	already_sorted(t_pushswap *ps, int option)
{
	t_stack	*tmp;

	tmp = (option == 'a') ? ps->top_a : ps->top_b;
	while (tmp)
	{
		if (!tmp->prev)
			return (0);
		else if (option == 'a' && tmp->prev->val < tmp->val)
			return (0);
		else if (option == 'b' && tmp->prev->val > tmp->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

inline static void	show_operand(int operand)
{
	if (operand == SA)
		ft_putendl("sa");
	else if (operand == SB)
		ft_putendl("sb");
	else if (operand == SS)
		ft_putendl("ss");
	else if (operand == PA)
		ft_putendl("pa");
	else if (operand == PB)
		ft_putendl("pb");
	else if (operand == RA)
		ft_putendl("ra");
	else if (operand == RB)
		ft_putendl("rb");
	else if (operand == RR)
		ft_putendl("rr");
	else if (operand == RRA)
		ft_putendl("rra");
	else if (operand == RRB)
		ft_putendl("rrb");
	else if (operand == RRR)
		ft_putendl("rrr");
}

int					main(int ac, char **av)
{
	t_pushswap	ps;
	t_stack		*elem;
	t_stack		*memory;

	if (ac-- < 2)
		return (0);
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
		return (ret_error(&ps));
	ps.abs_min = ps.min;
	if (!(already_sorted(&ps, 'a')))
		if (!sort_stack_c(&ps, ps.a))
			return (ret_error(&ps));
	squash_operand_stack(&ps);
	free_data_stack(&ps);
	memory = ps.instruction_begin;
	elem = ps.instruction_begin;
	ps.instruction_begin = NULL;
	while (elem)
	{
		show_operand(elem->val);
		elem = elem->next;
	}
	elem = NULL;
/*	if ((load_initial_stack(&ps, av, ac)))
		if (!(already_sorted(&ps, 'a')))
			if (backtrack_sort(&ps))
				elem = ps.instruction_begin;*/
	stackdel(&memory);
	return (0);
}
