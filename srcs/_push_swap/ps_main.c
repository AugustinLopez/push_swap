/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/02 18:10:05 by aulopez          ###   ########.fr       */
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

inline static size_t	ft_stksize(t_stack *elem)
{
	t_stack *tmp;
	size_t	n;

	n = 0;
	tmp = elem;
	while (tmp)
	{
		tmp = tmp->next;
		n++;
	}
	return (n);
}

int					main(int ac, char **av)
{
	t_pushswap	ps;
	t_stack		*instruction;
	char		**initial;

	if (ac-- < 2)
		return (0);
	ft_bzero(&ps, sizeof(ps));
	initial = av;
	if (!(load_initial_stack(&ps, ++av, ac)))
		return (ret_error(&ps));
	if (!(is_it_sorted(&ps, 'a')) && !sort_stack_a(&ps, ps.a))
		return (ret_error(&ps));
	squash_operand_stack(&ps);
	instruction = ps.instruction_begin;
	if (ac <= 500)
	{
		ps.instruction_begin = 0;
		stackdel(&ps.top_b);
		stackdel(&ps.top_a);
		av = initial;
		ft_bzero(&ps, sizeof(ps));
		if (!(load_initial_stack(&ps, ++av, ac)))
			return (ret_error(&ps));
		if (!(is_it_sorted(&ps, 'a')) && !sort_by_step(&ps, mode_greater))
			return (ret_error(&ps));
		squash_operand_stack(&ps);
		if (ft_stksize(instruction) <= ft_stksize(ps.instruction_begin))
			stackdel(&ps.instruction_begin);
		else
		{
			stackdel(&instruction);
			instruction = ps.instruction_begin;
		}
		ps.instruction_begin = 0;
		stackdel(&ps.top_b);
		stackdel(&ps.top_a);
		av = initial;
		ft_bzero(&ps, sizeof(ps));
		if (!(load_initial_stack(&ps, ++av, ac)))
			return (ret_error(&ps));
		if (!(is_it_sorted(&ps, 'a')) && !sort_by_step(&ps, mode_incremental))
			return (ret_error(&ps));
		squash_operand_stack(&ps);
		if (ft_stksize(instruction) <= ft_stksize(ps.instruction_begin))
			stackdel(&ps.instruction_begin);
		else
		{
			stackdel(&instruction);
			instruction = ps.instruction_begin;
		}
	}
	ps.instruction_begin = 0;
	stackdel(&ps.top_b);
	stackdel(&ps.top_a);
	show_list(instruction);
	stackdel(&instruction);
	return (0);
}
