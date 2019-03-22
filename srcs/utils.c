/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:21:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/22 14:30:32 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

void	show_list(t_pushswap *ps, int option)
{
	t_stack *elem;

	if (option == 'a')
		elem = ps->top_a;
	else
		elem = ps->top_b;
	while (elem)
	{
		ft_printf("%c.%d\n", option, elem->val);
		elem = elem->prev;
	}
}

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
}

void	stackdel(t_stack **elem)
{
	t_stack *tmp;

	if (*elem)
	{
		tmp = *elem;
		while (tmp->next)
		{
			tmp = (*elem)->next;
			free(*elem);
			*elem = tmp;
		}
	}
}

int					ret_error(t_pushswap *ps)
{
	free_data_stack(ps);
	stackdel(&(ps->instruction_begin));
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
