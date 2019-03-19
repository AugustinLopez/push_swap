/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_backtrack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:19:42 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/19 16:23:51 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

int	backtrack_stack(int option, t_pushswap *ps, size_t rr)
{
	size_t	c;
	int		r1;
	int		r2;

	c = (option == 'a') ? ps->a : ps->b;
	r1 = (option == 'a') ? RA : RB;
	r2 = (option == 'a') ? RRA : RRB;
	if (rr > c / 2)
	{
		while (c - rr++)
			if (!ps_operand(ps, r1, 1))
				return (0);
	}
	else
	{
		while (rr--)
			if (!ps_operand(ps, r2, 1))
				return (0);
	}
	return (1);
}
