/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:21:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 12:55:34 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

void	stackdelone(t_stack **elem)
{
	t_stack *tmp;

	if (*elem)
	{
		if ((*elem)->next)
			(*elem)->next->prev = (*elem)->prev;
		if ((*elem)->prev)
			(*elem)->prev->next = (*elem)->next;
		tmp = (*elem)->next;
		ft_memdel((void**)elem);
		*elem = tmp;
	}
	*elem = 0;
}

void	stackdel(t_stack **elem)
{
	t_stack *tmp;

	if (!*elem)
		return ;
	tmp = *elem;
	if (tmp->prev)
	{
		while (tmp->prev)
		{
			tmp = (*elem)->prev;
			free(*elem);
			*elem = tmp;
		}
	}
	else
	{
		while (tmp->next)
		{
			tmp = (*elem)->next;
			free(*elem);
			*elem = tmp;
		}
	}
	free(*elem);
	*elem = 0;
}

int		ret_error(t_pushswap *ps)
{
	stackdel(&(ps->top_a));
	stackdel(&(ps->top_b));
	stackdel(&(ps->instruction_begin));
	ft_putendl_fd("Error", 2);
	return (-1);
}

void	find_max_min(t_stack *elem, int *max, int *min)
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

int		is_it_sorted(t_pushswap *ps, int option)
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
