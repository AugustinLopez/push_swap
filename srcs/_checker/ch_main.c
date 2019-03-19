/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:57 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/19 17:01:48 by aulopez          ###   ########.fr       */
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

inline static int	checker_gnl(t_pushswap *ps, char *line)
{
	size_t	size;
	int		i;

	size = ft_strlen(line);
	if (3 > size || size > 4)
		return (-1);
	line[size - 1] = '\0';
	i = checker_operand(line);
	free(line);
	if (i != -1)
		ps_operand(ps, i, 0);
	return (i);
}

void	visualize(int option, t_pushswap *ps)
{
	t_stack	*elem;

	elem = (option == 'a') ? ps->top_a : ps->top_b;
	ft_printf("%c:", option - 32);
	while (elem)
	{
		if (!elem->next && elem->prev)
		{
			if ((option == 'a' && elem->val < elem->prev->val)
				|| (option == 'b' && elem->val > elem->prev->val))
				ft_putstr(FT_GREEN);
			else
				ft_putstr(FT_RED);
		}
		else if (elem->next && ((option == 'a' && elem->next->val < elem->val)
			|| (option == 'b' && elem->next->val > elem->val)))
			ft_putstr(FT_GREEN);
		else if ((option == 'b' && ps->b > 1) || (option == 'a' && ps->a > 1))
			ft_putstr(FT_RED);
		else
			ft_putstr(FT_GREEN);
		ft_printf("|%s", FT_EOC);
		elem = elem->prev;
	}
	ft_putchar('\n');
}

int	ch_available_option(char *av, int *flags)
{
	int	i;

	while (*(++av))
	{
		if (!(i = ft_strchri("v", av[0])))
			return (0);
		*flags |= (1 << (i - 1));
	}
	return (i);
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
		if (av[i][0] == '-' && ('0' <= av[i][1] || av[i][1] <= '9'))
			return (i);
		if (!ch_available_option(av[i], flags))
			return (0);
	}
	return (i);
}

int	main(int ac, char **av)
{
	t_pushswap	ps;
	int			operand;
	char		*line;

	if (ac < 2)
		return (0);
	ac -= 1;
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
		return (ret_error(&ps));
	while ((operand = ft_gnl(0, &line, 1)) > 0)
		if (checker_gnl(&ps, line) == -1)
			return (ret_error(&ps));
	if (operand == -1)
		return (ret_error(&ps));
	if ((operand = checker_is_it_sorted(&ps)))
		ft_putendl("OK");
	else
		ft_putendl("KO");
	visualize('a', &ps);
	free_all_stack(&ps);
	return (-1 * operand);
}
