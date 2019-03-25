/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 11:51:51 by aulopez          ###   ########.fr       */
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

int					main(int ac, char **av)
{
	t_pushswap	ps;

	if (ac-- < 2)
		return (0);
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, ++av, ac)))
		return (ret_error(&ps));
	if (!(is_it_sorted(&ps, 'a')) && !sort_stack_a(&ps, ps.a))
		return (ret_error(&ps));
	squash_operand_stack(&ps);
	show_list(ps.instruction_begin);
	stackdel(&ps.top_b);
	stackdel(&ps.top_a);
	stackdel(&ps.instruction_begin);
	return (0);
}
