/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:57 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:46:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	visualize_data(t_pushswap *ps, size_t l, int ac, char **av)
{
	t_stack	*tmp;

	if (!(load_initial_stack(ps, av, ac)))
		return (0);
	tmp = ps->top_a;
	ft_printf("Lines: %zu\n", l);
	ft_putstr("Array:");
	while (tmp)
	{
		ft_printf(" %d", tmp->val);
		tmp = tmp->prev;
	}
	stackdel(&ps->top_a);
	ft_putchar('\n');
	return (1);
}

inline static int	ch_ret(t_pushswap *ps, int ret)
{
	stackdel(&(ps->bot_a));
	stackdel(&(ps->bot_b));
	stackdel(&(ps->instruction_begin));
	return (ret);
}

inline static int	ch_checker(t_pushswap *ps, int flags, size_t *l)
{
	int		ret;
	char	*line;

	ch_visualize(ps, flags, 0);
	while ((ret = ft_gnl(0, &line, 1)) > 0 && ++(*l))
	{
		if (ch_gnl(ps, line, flags) == -1)
			return (0);
	}
	if (ret == -1)
		return (0);
	ret = is_it_sorted(ps, 'a');
	if (flags & CH_C)
		(!(ps->b) && ret) ? ft_putstr(FT_GREEN) : ft_putstr(FT_RED);
	(!(ps->b) && ret) ? ft_putendl("OK") : ft_putendl("KO");
	if (flags & CH_C)
		ft_putstr(FT_EOC);
	return (ch_ret(ps, 1));
}

inline static int	ch_help(void)
{
	ft_putstr(FT_UNDER "usage" FT_EOC ": " FT_BOLD "./checker " FT_EOC);
	ft_putstr("[" FT_BOLD "-vcsfidh" FT_EOC "] [" FT_UNDER"int" FT_EOC " ");
	ft_putendl(FT_UNDER "..." FT_EOC "]");
	ft_putendl("\n\tThe following options are available:");
	ft_putendl(FT_BOLD "\n\t-v" FT_EOC "\tgraphical view");
	ft_putendl(FT_BOLD "\t-c" FT_EOC "\tgraphical view with color");
	ft_putendl(FT_BOLD "\t-s" FT_EOC "\tslower sorting");
	ft_putendl(FT_BOLD "\t-f" FT_EOC "\tfaster sorting");
	ft_putendl(FT_BOLD "\t-i" FT_EOC "\tinstant sorting");
	ft_putendl(FT_BOLD "\t-d" FT_EOC "\tshow additional data");
	ft_putendl(FT_BOLD "\t-h" FT_EOC "\thelp\n");
	return (0);
}

int					main(int ac, char **av)
{
	t_pushswap	ps;
	int			operand;
	int			flags;
	size_t		l;

	l = 0;
	flags = 0;
	operand = ch_parsing(ac, av, &flags);
	if (flags & CH_H)
		return (ch_help());
	if (ac - operand < 1)
		return (0);
	ac -= operand;
	av += operand;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)) || !(define_index(&ps)))
		return (ret_error(&ps, 1));
	if (ps.a > 500)
		flags &= ~CH_V;
	if (!ch_checker(&ps, flags, &l))
		return (ret_error(&ps, 1));
	if (flags & CH_D)
		if (!visualize_data(&ps, l, ac, av))
			return (-1);
	return (-1 * operand);
}
