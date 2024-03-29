/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:21:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 12:48:26 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

int					ret_error(t_pushswap *ps, int option)
{
	stackdel(&(ps->top_a));
	stackdel(&(ps->top_b));
	stackdel(&(ps->instruction_begin));
	if (option)
		ft_putendl_fd("Error", 2);
	return (-1);
}

void				find_max_min(t_stack *elem, int *max, int *min)
{
	t_stack *tmp;

	*max = INT_MIN;
	*min = INT_MAX;
	if (elem)
	{
		tmp = elem;
		while (tmp)
		{
			if (tmp->val > *max)
				*max = tmp->val;
			if (tmp->val < *min)
				*min = tmp->val;
			tmp = tmp->prev;
		}
	}
}

int					is_it_sorted(t_pushswap *ps, int option)
{
	t_stack	*tmp;

	tmp = (option == 'a') ? ps->top_a : ps->top_b;
	while (tmp)
	{
		if (!tmp->prev)
			return (1);
		else if (option == 'a' && tmp->prev->val < tmp->val)
			return (0);
		else if (option == 'b' && tmp->prev->val > tmp->val)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}
