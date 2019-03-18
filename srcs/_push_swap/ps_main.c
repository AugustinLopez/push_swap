/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/18 11:21:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pushswap.h>

void	show_list(t_pushswap *ps, int option)
{
	t_stack *elem;

	if (option == 'a')
		elem = ps->top_a;
	else
		elem = ps->top_b;
	while (elem)
	{
		ft_printf("%c.%d\n",option, elem->val);
		elem = elem->prev;
	}
}
/*
** Add "" and '' parsing later
*/

static int		already_sorted(t_pushswap *ps)
{
	t_stack	*tmp;

	tmp = ps->top_a;
	while (tmp)
	{
		if (tmp->prev && tmp->prev->val < tmp->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

void	show_instruction(t_stack *instruction)
{
	t_stack *elem;

	elem = instruction;
	while (elem)
	{
		if (elem->val == SA)
			ft_putendl("sa");
		else if (elem->val == SB)
			ft_putendl("sb");
		else if (elem->val == SS)
			ft_putendl("ss");
		else if (elem->val == PA)
			ft_putendl("pa");
		else if (elem->val == PB)
			ft_putendl("pb");
		else if (elem->val == RA)
			ft_putendl("ra");
		else if (elem->val == RB)
			ft_putendl("rb");
		else if (elem->val == RR)
			ft_putendl("rr");
		else if (elem->val == RRA)
			ft_putendl("rra");
		else if (elem->val == RRB)
			ft_putendl("rrb");
		else if (elem->val == RRR)
			ft_putendl("rrr");
		elem = elem->next;
	}
}

int				main(int ac, char **av)
{
	t_pushswap	ps;

	if (ac < 2)
		return (0);
	ac -= 2;
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
	{
		free_all_stack(&ps);
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	if (!(already_sorted(&ps)))
		sort_stack_a(&ps, ps.a);
	squash_instruction(&ps);
	show_instruction(ps.instruction_begin);
	//show_list(&ps, 'a');
	free_all_stack(&ps);
	return (0);
}
