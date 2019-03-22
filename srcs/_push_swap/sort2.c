/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:26:29 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/22 19:01:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

/*inline static int	loop_quicksort_b(t_pushswap *ps, int pivot,
									size_t *rb, size_t *pa)
{
	if (ps->top_b->val < pivot && ++(*pa))
	{
		if (!ps_operand(ps, PA, 1))
			return (0);
		while (ps->top_a && ps->top_a->val == ps->min)
		{
			if (!ps_operand(ps, RA, 1))
				return (0);
			update_min(ps);
		}
	}
	else if (++(*rb) && !ps_operand(ps, RB, 1))
		return (0);
	return (1);
}

inline static int	sort_stack_b(t_pushswap *ps, size_t len)
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
	if (!(pivot = get_pivot('b', ps, len, &i)) && i)
		return (0);
	while (other_push_needed('b', ps, len - i, pivot) && i++ < len)
		if (!loop_quicksort_b(ps, pivot, &rb, &pa))
			return (0);
	if (!sort_stack_b(ps, len - pa)
		|| !backtrack_stack('b', ps, rb)
		|| !sort_stack_c(ps, pa))
		return (0);
	while (ps->a && pa--)
	{
		while (ps->top_a && ps->top_a->val == ps->min)
		{
			if (!ps_operand(ps, RA, 1))
				return (0);
			update_min(ps);
		}
		if (ps->top_a->val != ps->abs_min && !ps_operand(ps, PB, 1))
			return (0);
	}
	return (1);
}*/

/*

inline static int is_it_sorted(int option, t_pushswap *ps)
{
	t_stack *elem;

	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (option == 'a')
		{
			if (elem->prev && elem->val > elem->prev->val)
				return (0);
		}
		if (option == 'b')
		{
			if (elem->prev && elem->val < elem->prev->val)
				return (0);
		}
		elem = elem->prev;
	}
	return (1);
}*/

int				ft_push1(t_pushswap *ps);


inline static int	other_push_needed(int option, t_pushswap *ps,
										size_t len, int pivot)
{
	t_stack	*elem;

	elem = option == 'a' ? ps->top_a : ps->top_b;
	while (len-- && elem)
	{
		if ((option == 'a' && elem->val < pivot)
			|| (option == 'b' && elem->val > pivot))
			return (1);
		elem = elem->prev;
	}
	return (0);
}

inline static int	get_max(int option, t_pushswap *ps)
{
	t_stack *elem;
	int		max;

	max = INT_MIN;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->val > max)
			max = elem->val;
		elem = elem->prev;
	}
	return (max);
}


inline static int	get_min(int option, t_pushswap *ps)
{
	t_stack *elem;
	int		min;

	min = INT_MAX;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->val < min)
			min = elem->val;
		elem = elem->prev;
	}
	return (min);
}


inline static void	update_min(t_pushswap *ps)
{
	t_stack	*elem;
	int		min;

	min = INT_MAX;
	elem = ps->top_a;
	while (elem)
	{
		if (elem->val < min && elem->val > ps->min)
			min = elem->val;
		elem = elem->prev;
	}
	elem = ps->top_b;
	while (elem)
	{
		if (elem->val < min && elem->val > ps->min)
			min = elem->val;
		elem = elem->prev;
	}
	ps->min = min;
}

int				rotate(t_pushswap *ps)
{
	size_t	i;
	int	max;
	t_stack	*elem;

	max = get_max('a', ps);
	i = 0;
	elem = ps->bot_a;
	while (i++ < ps->a || !elem)
	{
		if (elem->val == max)
			break ;
		elem = elem->next;
	}
	if (i <= ps->a / 2)
	{
		if (!ps_operand(ps, RRB, 1))
			return (0);
	}
	else if (!(ps_operand(ps, RB, 1)))
		return (0);
	return (1);
}

int				get_max_to_a(t_pushswap *ps)
{
	int	max;

	max = get_max('b', ps);
	if (ps->top_b->val == max)
	{
		if (!ps_operand(ps, PA, 1))
			return (0);
	}
	else if (ps->top_b->val == ps->min)
	{
		if (!ps_operand(ps, PA, 1) || !ps_operand(ps, RA, 1))
			return (0);
		update_min(ps);
	}
	else if (!rotate(ps))
		return (0);
	return (1);
}

int				split_to_a(t_pushswap *ps, int pivot)
{
	size_t	i;

	i = ps->b;
	while (i--)
	{
		if (ps->b < 13)
			get_max_to_a(ps);
		else if (ps->top_b->val >= pivot)
		{
			if (!ps_operand(ps, PA, 1))
				return (0);
		}
		else
		{
			if (ps->top_b->val == ps->min)
			{
				if (!ps_operand(ps, PA, 1) || !ps_operand(ps, RA, 1))
					return (0);
				update_min(ps);
			}
			else if (!ps_operand(ps, RB, 1))
				return (0);
		}
	}
	return (1);
}

size_t		find_value(int option, t_pushswap *ps, int val)
{
	t_stack *elem;
	size_t	i;

	i = 1;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	while (elem)
	{
		if (elem->val == val)
			return (i);
		i++;
		elem = elem->prev;
	}
	return (0);
}

int				ft_push3(t_pushswap *ps)
{
	size_t	len;
	size_t	i;
	size_t	c;
	int		max;
	int		pivot;

	c = 0;
	len = find_value('a', ps, ps->abs_min) - 1;
	i = 0;
	if (!(pivot = get_pivot('a', ps, len - 1, &i)) && i)
		return (0);
	while (other_push_needed('a', ps, len - i, pivot))
	{
		if (ps->top_a->val < pivot)
		{
			if (!ps_operand(ps, PB, 1))
				return (0);
		}
		else if (!ps_operand(ps, RA, 1) && ++c)
			return (0);
	}
	i = 0;
	max = get_max('b', ps);
	while (i++ < c)
	{
		if (ps->top_b->val == max)
		{
			if (!(ps_operand(ps, RRA, 1) || !(ps_operand(ps, RRB, 1))))
				return (0);
		}
		else if (!(ps_operand(ps, RRA, 1)))
			return (0);
	}
	/*if (c > 0)
		ft_push1(ps);*/
	return (1);
}

int				ft_push2(t_pushswap *ps, int max)
{
	while (ps->min <= max && ps->top_a->val != ps->abs_min)
	{
		if (ps->top_a->val == ps->min)
		{
			if (!ps_operand(ps, RA, 1))
				return (0);
			update_min(ps);
		}
		else if (!ps_operand(ps, PB, 1))
			return (0);
	}
	if (ps->b && get_min('b', ps) > get_max('a', ps))
		ft_push1(ps);
	return (1);
}

int				ft_push1(t_pushswap *ps)
{
	int	max;
	int	pivot;
	size_t	i;

	if (!ps->b)
		return (1);
	max = get_max('b', ps);
	i = 0;
	if (!(pivot = get_pivot('b', ps, ps->b, &i)) && i)
		return (0);
	split_to_a(ps, pivot);
	ft_push1(ps);
	while (ps->top_a->val == ps->min)
	{
		if (!ps_operand(ps, RA, 1))
			return (0);
		update_min(ps);
	}
	/*if (find_value('a', ps, ps->abs_min) >= 20)
		ft_push3(ps);*/
	ft_push2(ps, max);
	return (1);
}



int					initial_split(t_pushswap *ps)
{
	int		pivot;
	size_t	i;

	i = 0;
	if (!(pivot = get_pivot('a', ps, ps->a, &i)) && i)
		return (0);
	while (other_push_needed('a', ps, ps->a - i, pivot))
	{
		if (ps->top_a->val < pivot)
		{
			if (!ps_operand(ps, PB, 1))
				return (0);
		}
		else if (!ps_operand(ps, RA, 1))
			return (0);
	}
	return (1);
}

int					sort_stack_c(t_pushswap *ps, size_t len)
{
	int	max;

	if (len <= 3 || (len == 4 && ps->a == 4))
		return (sort_little_a(ps, len));
	if (!initial_split(ps))
		return (0);
	ft_push1(ps);
	/*if (find_value('a', ps, ps->abs_min) - 1 >= 20)
	{
		max = get_max('a', ps);
		ft_push3(ps, max);
		max = get_max('a', ps);
		ft_push3(ps, max);
	}*/
	max = get_max('a', ps);
	ft_push2(ps, max);
	return (1);
}
