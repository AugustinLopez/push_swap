/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:57 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/22 16:04:28 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	checker_operand(char *buf)
{
	if (!ft_strcmp(buf, "sa"))
		return (SA);
	if (!ft_strcmp(buf, "sb"))
		return (SB);
	if (!ft_strcmp(buf, "ss"))
		return (SS);
	if (!ft_strcmp(buf, "pa"))
		return (PA);
	if (!ft_strcmp(buf, "pb"))
		return (PB);
	if (!ft_strcmp(buf, "ra"))
		return (RA);
	if (!ft_strcmp(buf, "rb"))
		return (RB);
	if (!ft_strcmp(buf, "rr"))
		return (RR);
	if (!ft_strcmp(buf, "rra"))
		return (RRA);
	if (!ft_strcmp(buf, "rrb"))
		return (RRB);
	if (!ft_strcmp(buf, "rrr"))
		return (RRR);
	return (-1);
}

inline static int	checker_is_it_sorted(t_pushswap *ps)
{
	t_stack *stack;

	if (ps->bot_b)
		return (0);
	stack = ps->top_a;
	while (stack)
	{
		if (stack->prev && stack->val > stack->prev->val)
			return (0);
		stack = stack->prev;
	}
	return (1);
}

void	choose_color(int option, t_pushswap *ps, t_stack *elem, char *oper)
{
	if (oper && option == 'a' && ps->a)
	{
		if ((!ft_strcmp(oper, "sa") || !ft_strcmp(oper, "ss")) && (elem == ps->top_a || elem == ps->top_a->prev))
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
		if ((!ft_strcmp(oper, "sb") || !ft_strcmp(oper, "ss")) && (elem == ps->top_b || elem == ps->top_b->prev))
			ft_putstr(FT_YELLOW);
		else if ((!ft_strcmp(oper, "rb") || !ft_strcmp(oper, "rr")))
			ft_putstr(FT_GREEN);
		else if ((!ft_strcmp(oper, "rrb") || !ft_strcmp(oper, "rrr")))
			ft_putstr(FT_RED);
		else if (!ft_strcmp(oper, "pb") && elem == ps->top_b)
			ft_putstr(FT_CYAN);
	}
}

void	visualize(t_pushswap *ps, char *oper, int flags)
{
	size_t	top;
	size_t	decal;
	t_stack *aaa;
	t_stack *bbb;

	decal = ft_nprintf("%d", ps->max);
	write(1, "\n", 1);
	top = ps->a + ps->b;
	while (top > ps->a && top > ps->b)
	{
		write(1, "\n", 1);
		top--;
	}
	aaa = ps->top_a;
	bbb = ps->top_b;
	while (top)
	{
		if (top > ps->a)
		{
			if (flags & CH_C)
				choose_color('b', ps, bbb, oper);
			ft_printf("%*c   ", decal + ps->max, ' ');
			ft_printf("%*d %#*c\n", decal, bbb->val, bbb->val, '|');
			ft_putstr(FT_EOC);
			bbb = bbb->prev;
		}
		else if (top > ps->b)
		{
			if (flags & CH_C)
				choose_color('a', ps, aaa, oper);
			ft_printf("%-*d %#*c\n", decal, aaa->val, aaa->val, '|');
			ft_putstr(FT_EOC);
			aaa = aaa->prev;
		}
		else
		{
			if (flags & CH_C)
				choose_color('a', ps, aaa, oper);
			ft_printf("%-*d %#*c%#*c", decal, aaa->val, aaa->val, '|', ps->max - aaa->val + 1, ' ');
			ft_putstr(FT_EOC);
			if (flags & CH_C)
				choose_color('b', ps, bbb, oper);
			ft_printf(" %*d %#*c\n", decal, bbb->val, bbb->val, '|');
			ft_putstr(FT_EOC);
			aaa = aaa->prev;
			bbb = bbb->prev;
		}
		top--;
	}
}


void	visualize_helper(t_pushswap *ps, int flags, char *oper)
{
	if (ps->min != 1)
		flags &= ~CH_V;
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

inline static int	checker_gnl(t_pushswap *ps, char *line, int flags)
{
	size_t	size;
	int		i;

	size = ft_strlen(line);
	if (3 > size || size > 4)
		return (-1);
	line[size - 1] = '\0';
	i = checker_operand(line);
	if (i != -1)
	{
		ps_operand(ps, i, 0);
		visualize_helper(ps, flags, line);
	}
	free(line);
	return (i);
}

int	ch_available_option(char *av, int *flags)
{
	int	i;

	while (*(++av))
	{
		if (!(i = ft_strchri("vcSFI", av[0])))
			return (0);
		*flags |= (1 << (i - 1));
	}
	return (1);
}

int	ch_parsing(int ac, char **av, int *flags)
{
	int	i;

	i = 0;
	*flags = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-' && !av[i][2])
			return (i + 1);
		if (av[i][0] == '-' && ('0' <= av[i][1] && av[i][1] <= '9'))
			return (i);
		if (!ch_available_option(av[i], flags))
			return (0);
	}
	if (*flags)
		*flags |= CH_V;
	return (i);
}

int	main(int ac, char **av)
{
	t_pushswap	ps;
	int			operand;
	char		*line;
	int			flags;

	flags = 0;
	operand = ch_parsing(ac, av, &flags);
	if (ac - operand < 1)
		return (0);
	ac -= operand;
	av += operand;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
		return (ret_error(&ps));
	if (ps.min != 1 || ps.max != ac || ps.max > 500)
		flags &= ~CH_V;
	visualize_helper(&ps, flags, 0);
	while ((operand = ft_gnl(0, &line, 1)) > 0)
		if (checker_gnl(&ps, line, flags) == -1)
			return (ret_error(&ps));
	if (operand == -1)
		return (ret_error(&ps));
	if ((operand = checker_is_it_sorted(&ps)))
		ft_putendl("OK");
	else
		ft_putendl("KO");
	free_data_stack(&ps);
	stackdel(&(ps.instruction_begin));
	return (-1 * operand);
}
