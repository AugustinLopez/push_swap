/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/04 11:24:02 by aulopez          ###   ########.fr       */
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

static int	other_push_needed(int option, t_pushswap *ps, size_t len, int pivot)
{
	t_stack	*elem;

	elem = option == 'a' ? ps->top_a : ps->top_b;
	while (len--)
	{
		if ((option == 'a' && elem->val < pivot)
			|| (option == 'b' && elem->val > pivot))
			return (1);
		elem = elem->prev;
	}
	return (0);
}

static int	backtrack_stack(int option, t_pushswap *ps, size_t rr)
{
	if (option == 'a')
	{
		if (rr > ps->a / 2)
			while (ps->a - rr++)
				ps_operand(ps, RA, 1);
		else
			while (rr--)
				ps_operand(ps, RRA, 1);
	}
	else if (option == 'b')
	{
		if (rr > ps->b / 2)
			while (ps->b - rr++)
				ps_operand(ps, RB, 1);
		else
			while (rr--)
				ps_operand(ps, RRB, 1);
	}
	return (0);
}

static int	sort_stack_b(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	rb;
	size_t	pa;
	size_t	i;

	rb = 0;
	pa = 0;
	i = 0;
	if (len <= 3)
		return (sort_little_b(ps, len));
	pivot = get_pivot('b', ps, len);
	while (other_push_needed('b', ps, len - i, pivot) && i++ < len)
	{
		if (ps->top_b->val > pivot)
		{
			pa++;
			ps_operand(ps, PA, 1);
		}
		else
		{
			rb++;
			ps_operand(ps, RB, 1);
		}
	}
	sort_stack_a(ps, pa);
	backtrack_stack('b', ps, rb);
	sort_stack_b(ps, len - pa);
	while (pa--)
		ps_operand(ps, PB, 1);
	return (0);
}

int			sort_stack_a(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	ra;
	size_t	pb;
	size_t	i;

	ra = 0;
	pb = 0;
	i = 0;
	if (len <= 3)
		return (sort_little_a(ps, len));
	pivot = get_pivot('a', ps, len);
	while (other_push_needed('a', ps, len - i, pivot) && i++ < len)
	{
		if (ps->top_a->val < pivot)
		{
			pb++;
			ps_operand(ps, PB, 1);
		}
		else
		{
			ra++;
			ps_operand(ps, RA, 1);
		}
	}
	backtrack_stack('a', ps, ra);
	sort_stack_a(ps, len - pb);
	sort_stack_b(ps, pb);
	while (pb--)
		ps_operand(ps, PA, 1);
	return (0);
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
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	if (!(already_sorted(&ps)))
		sort_stack_a(&ps, ps.a);
	show_instruction(ps.instruction_begin);
	//show_list(&ps, 'a');
	free_all_stack(&ps);
	return (0);
}
