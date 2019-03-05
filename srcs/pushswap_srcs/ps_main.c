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

void	show_tab(t_pushswap *ps)
{
	t_stack *tmp;

	tmp = ps->top_a;
	while (tmp)
	{
		ft_printf("%d\n", ps->top_a->val);
		tmp = tmp->prev;
	}
}

void	find_min_max(t_pushswap *ps, size_t *i, size_t *j)
{
	t_stack *tmp;

	ps->min_a = ps->top_a->val;
	ps->max_a = ps->top_a->val;
	tmp = ps->top_a->prev;
	*i = 0;
	*j = 0;
	while (tmp)
	{
		if (tmp->val > ps->max_a)
			ps->max_a = tmp->val;
		if (tmp->val < ps->min_a)
			ps->min_a = tmp->val;
		tmp->val > tmp->next->val ? (*i)++ : (*j)++;
		tmp = tmp->prev;
	}
	ps->top_a->val > ps->bot_a->val ? (*i)++ : (*j)++;
}

// need a fonction to choose between rotate_till and reverse_till
void	rotate_till(t_pushswap *ps)
{
	t_stack *tmp;
	size_t	c;

	c = 1;
	tmp = ps->top_a;
	while (tmp)
	{
		if (tmp->val == ps->min_a)
			break;
		c++;
		tmp = tmp->prev;
	}
	c = (c <= ps->a / 2) || (c <= (ps->a + 1) / 2) ? 1 : 0;
	while (ps->bot_a->val != ps->max_a)
	{
		if (c)
		{
			ps_rotate(ps, RA);
			ft_putendl("ra");
		}
		else
		{
			ps_reverse_rotate(ps, RRA);
			ft_putendl("rra");
		}
	}
	while (ps->bot_b)
	{
		ps_push(ps, PA);
		ft_putendl("pa");
	}
}

size_t	new_find_min_max(t_pushswap *ps, size_t	*index_min)
{
	t_stack *tmp;
	size_t	num;
	size_t	index;

	ps->min_a = ps->top_a->val;
	ps->max_a = ps->top_a->val;
	tmp = ps->top_a->prev;
	num = 0;
	*index_min = 0;
	index = 0;
	while (tmp)
	{
		index++;
		if (tmp->val > ps->max_a)
			ps->max_a = tmp->val;
		if (tmp->val < ps->min_a)
		{
			ps->min_a = tmp->val;
			*index_min = index;
		}
		tmp->val > tmp->next->val ? num++ : 0;
		tmp = tmp->prev;
	}
	ps->top_a->val > ps->bot_a->val ? num++ : 0;
	return (num);
}

/*void	my_sorting_algorithm(t_pushswap *ps, size_t incr)
{
	size_t	i;
	size_t	j;

	if (ps->top_a->val > ps->top_a->prev->val)
	{
		incr++;
		ps_swap(ps, SA);
		ft_putendl("sa");
	}
	i = ps->a;
	while (i > 2 && (!incr || incr - 1 < (ps->a))) //need to solve size_t vs int
	{
		j = 0;
		while (j < i - 1)
		{
			if (ps->top_a->val == ps->min_a)
				break;
			ps_reverse_rotate(ps, RRA);
			ft_putendl("rra");
			if (ps->top_a->val == ps->min_a)
				break;
			if (ps->top_a->val > ps->top_a->prev->val)
			{
				incr++;
				ps_swap(ps, SA);
				ft_putendl("sa");
			}
			j++;
		}
		i--;
		if (i > 2 && (!incr || incr - 1 < (ps->a)))
		{
			ps_push(ps, PB);
			ft_putendl("pb");
		}
	}
	rotate_till(ps);
}*/

void	my_new_sorting_algorithm(t_pushswap *ps)
{
	size_t	order;
	size_t	index_min;
	int		i;

	i = 0;
	order = new_find_min_max(ps, &index_min);
	while (1)
	{
		order = new_find_min_max(ps, &index_min);
		if (order + 1 >= ps->a)
		{
			rotate_till(ps);
			return ;
		}
		if (ps->top_a->val > ps->top_a->prev->val)
		{
			ps_swap(ps, SA);
			ft_putendl("sa");
			order = new_find_min_max(ps, &index_min);
		}
		if (ps->top_a->val == ps->min_a)
		{
			while (ps->top_a->val == ps->min_a && order + 1 < ps->a)
			{
				ps_push(ps, PB);
				ft_putendl("pb");
				new_find_min_max(ps, &index_min);
			}
			continue ;
		}
		ps_reverse_rotate(ps, RRA);
		ft_putendl("rra");
	}
}

int		main(int ac, char **av)
{
	t_pushswap	ps;

	if (ac == 1 || ac == 2)
		return (0);
	ac -= 2;
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
	{
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	my_new_sorting_algorithm(&ps);
	/*find_min_max(&ps, &increasing, &decreasing);
	if (increasing + 1 == (ps.a))
		rotate_till(&ps);
	else
		my_sorting_algorithm(&ps, increasing);*/
	/*else if (-incr == ps.a)
		(void)incr; //inverse list
	else if (-incr + 1 == ps.a)
		(void)incr; //rotate things around and inverse*/
	free_stack(&ps);
}
