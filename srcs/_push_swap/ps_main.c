/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:17:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

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

inline static void	show_list(t_stack *elem)
{
	t_stack *tmp;

	tmp = elem;
	while (tmp)
	{
		show_operand(tmp->val);
		tmp = tmp->next;
	}
}

void				algo_end(t_pushswap *ps, t_stack **elem, int option)
{
	if (!option)
	{
		squash_operand_stack(ps);
		stackdel(&(ps->top_b));
		stackdel(&(ps->top_a));
	}
	if (elem)
	{
		if (ft_stksize(*elem) <= ft_stksize(ps->instruction_begin))
		{
			stackdel(&(ps->instruction_begin));
			ps->instruction_begin = *elem;
		}
		else
			stackdel(elem);
	}
}

int					sub_main(t_pushswap *ps, int ac, char **av)
{
	t_stack	*instruction;

	if (!(load_initial_stack(ps, av, ac))
		|| (!(is_it_sorted(ps, 'a')) && !sort_by_step(ps, mode_greater)))
		return (ret_error(ps, 0));
	algo_end(ps, 0, 0);
	instruction = ps->instruction_begin;
	if (!(load_initial_stack(ps, av, ac))
		|| (!(is_it_sorted(ps, 'a')) && !sort_by_step(ps, mode_incremental)))
	{
		(void)ret_error(ps, 0);
		ps->instruction_begin = instruction;
		return (0);
	}
	algo_end(ps, &instruction, 0);
	return (0);
}

int					main(int ac, char **av)
{
	t_pushswap	ps;
	t_stack		*instruction;
	size_t		size;

	if (ac-- < 2)
		return (0);
	if (!(load_initial_stack(&ps, ++av, ac))
		|| (!(is_it_sorted(&ps, 'a')) && !sort_stack_a(&ps, ps.a)))
		return (ret_error(&ps, 1));
	size = ps.a;
	algo_end(&ps, 0, 0);
	instruction = ps.instruction_begin;
	if (size <= 500 && !sub_main(&ps, ac, av))
		algo_end(&ps, &instruction, 1);
	show_list(ps.instruction_begin);
	stackdel(&ps.instruction_begin);
	return (0);
}
