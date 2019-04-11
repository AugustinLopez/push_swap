/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertsort_step2_nbr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:13:09 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:17:48 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

static inline int		is_mid(t_move *rrx, size_t size, size_t index)
{
	size_t	prev;
	size_t	new;

	prev = rrx->i > size / 2 ? rrx->i - size / 2 : size / 2 - rrx->i;
	new = index > size / 2 ? index - size / 2 : size / 2 - index;
	if (prev > new)
	{
		rrx->i = index;
		return (4);
	}
	return (0);
}

static inline size_t	calc(int option, t_move *rrx, size_t r1, size_t r2)
{
	size_t	real;
	int		case_equal;

	case_equal = 0;
	if (option > 4)
	{
		option -= 4;
		case_equal = 1;
	}
	if (option == 1 || option == 2)
		real = (r1 < r2) ? r2 : r1;
	else
		real = r1 + r2;
	if (rrx->real > real || (rrx->real == real && case_equal))
	{
		rrx->real = real;
		rrx->rra = (option == 2 || option == 4) * r1;
		rrx->rrb = (option == 2 || option == 3) * r2;
		rrx->ra = (option == 1 || option == 3) * r1;
		rrx->rb = (option == 1 || option == 4) * r2;
	}
	return (real);
}

int						nbr_move_to_a(t_move *temp, t_move *rrx,
											size_t size, size_t index)
{
	size_t	rr;
	size_t	rrr;
	size_t	rab;
	size_t	rba;

	rr = temp->ra < temp->rb ? temp->rb : temp->ra;
	rrr = temp->rra < temp->rrb ? temp->rrb : temp->rra;
	rab = temp->ra + temp->rrb;
	rba = temp->rra + temp->rb;
	if (rr <= rrr && rr <= rab && rr <= rba)
		return (calc(1 + is_mid(rrx, size, index), rrx, temp->ra, temp->rb));
	else if (rrr <= rr && rrr <= rab && rrr <= rba)
		return (calc(2 + is_mid(rrx, size, index), rrx, temp->rra, temp->rrb));
	else if (rab <= rrr && rab <= rrr && rab <= rba)
		return (calc(3 + is_mid(rrx, size, index), rrx, temp->ra, temp->rrb));
	return (calc(4 + is_mid(rrx, size, index), rrx, temp->rra, temp->rb));
}
