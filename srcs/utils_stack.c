/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:21:45 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 12:48:37 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

size_t				ft_stksize(t_stack *elem)
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

void				stackdelone(t_stack **elem)
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

void				stackdel(t_stack **elem)
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
			ft_memdel((void **)elem);
			*elem = tmp;
		}
	}
	else if (tmp->next)
	{
		while (tmp->next)
		{
			tmp = (*elem)->next;
			ft_memdel((void **)elem);
			*elem = tmp;
		}
	}
	tmp ? ft_memdel((void **)&tmp) : 0;
	*elem = 0;
}
