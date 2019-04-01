/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_show_sorting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:21:10 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 14:17:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static void	choose_color(int option, t_pushswap *ps, t_stack *elem,
									char *oper)
{
	if (oper && option == 'a' && ps->a)
	{
		if ((!ft_strcmp(oper, "sa") || !ft_strcmp(oper, "ss"))
			&& (elem == ps->top_a || elem == ps->top_a->prev))
			ft_putstr(FT_YELLOW);
		else if ((!ft_strcmp(oper, "ra") || !ft_strcmp(oper, "rr")))
			ft_putstr(FT_GREEN);
		else if ((!ft_strcmp(oper, "rra") || !ft_strcmp(oper, "rrr")))
			ft_putstr(FT_RED);
		else if (!ft_strcmp(oper, "pa") && elem == ps->top_a)
			ft_putstr(FT_CYAN);
	}
	else if (oper && option == 'b' && ps->b)
	{
		if ((!ft_strcmp(oper, "sb") || !ft_strcmp(oper, "ss"))
			&& (elem == ps->top_b || elem == ps->top_b->prev))
			ft_putstr(FT_YELLOW);
		else if ((!ft_strcmp(oper, "rb") || !ft_strcmp(oper, "rr")))
			ft_putstr(FT_GREEN);
		else if ((!ft_strcmp(oper, "rrb") || !ft_strcmp(oper, "rrr")))
			ft_putstr(FT_RED);
		else if (!ft_strcmp(oper, "pb") && elem == ps->top_b)
			ft_putstr(FT_CYAN);
	}
}

inline static void	show_one(t_pushswap *ps, t_visualize *visu)
{
	if (visu->total > ps->a)
	{
		if (visu->flags & CH_C)
			choose_color('b', ps, visu->b, visu->oper);
		ft_printf("%*c   ", visu->offset + ps->a + ps->b, ' ');
		ft_printf("%*d %#*c\n", visu->offset, visu->b->val, visu->b->index + 1, '|');
		ft_putstr(FT_EOC);
		visu->b = visu->b->prev;
	}
	else if (visu->total > ps->b)
	{
		if (visu->flags & CH_C)
			choose_color('a', ps, visu->a, visu->oper);
		ft_printf("%*d %#*c\n", visu->offset, visu->a->val, visu->a->index + 1, '|');
		ft_putstr(FT_EOC);
		visu->a = visu->a->prev;
	}
}

inline static void	show_both(t_pushswap *ps, t_visualize *visu)
{
	if (visu->flags & CH_C)
		choose_color('a', ps, visu->a, visu->oper);
	ft_printf("%*d %#*c", visu->offset, visu->a->val, visu->a->index + 1, '|');
	ft_printf("%#*c", ps->a + ps->b - visu->a->index + 1, ' ');
	ft_putstr(FT_EOC);
	if (visu->flags & CH_C)
		choose_color('b', ps, visu->b, visu->oper);
	ft_printf(" %*d %#*c\n", visu->offset, visu->b->val, visu->b->index + 1, '|');
	ft_putstr(FT_EOC);
	visu->a = visu->a->prev;
	visu->b = visu->b->prev;
}

inline static void	visualize(t_pushswap *ps, char *oper, int flags)
{
	t_visualize		visu;
	unsigned int	i;

	write(1, "\n", 1);
	visu.offset = ft_nprintf("%d", ps->max);
	i = ft_nprintf("%d", ps->min);
	visu.offset = i > visu.offset ? i : visu.offset;
	visu.a = ps->top_a;
	visu.b = ps->top_b;
	visu.oper = oper;
	visu.flags = flags;
	visu.total = ps->a + ps->b;
	while (visu.total > ps->a && visu.total > ps->b)
	{
		write(1, "\n", 1);
		visu.total--;
	}
	while (visu.total)
	{
		if (visu.total > ps->a || visu.total > ps->b)
			show_one(ps, &visu);
		else
			show_both(ps, &visu);
		visu.total--;
	}
}

void				ch_visualize(t_pushswap *ps, int flags, char *oper)
{
	if (flags & CH_V)
	{
		visualize(ps, oper, flags);
		if (oper)
			ft_printf("Operation is : %s\n", oper);
		if (flags & CH_S)
			usleep(200000);
		else if (flags & CH_F)
			usleep(5000);
		else if (!(flags & CH_I))
			usleep(50000);
	}
}
