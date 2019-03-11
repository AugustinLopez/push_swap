/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:17:50 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/04 11:24:02 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pushswap.h>

void	show_tab(t_pushswap *ps)
{
	t_stack *tmp;

	tmp = ps->top_a;
	while (tmp)
	{
		ft_printf("%d\n", ps->top_a->val);
		tmp = tmp->prev;
	}
}

void	rotate_till(t_pushswap *ps)
{
	t_stack *tmp;
	size_t	c;

	c = 1;
	tmp = ps->top_a;
	while (tmp)
	{
		if (tmp->val == ps->min_a)
			break;
		c++;
		tmp = tmp->prev;
	}
	c = (c <= ps->a / 2) || (c <= (ps->a + 1) / 2) ? 1 : 0;
	while (ps->bot_a->val != ps->max_a)
	{
		if (c)
		{
			ps_rotate(ps, RA);
			ft_putendl("ra");
		}
		else
		{
			ps_reverse_rotate(ps, RRA);
			ft_putendl("rra");
		}
	}
	while (ps->bot_b)
	{
		ps_push(ps, PA);
		ft_putendl("pa");
	}
}

int		main(int ac, char **av)
{
	t_pushswap	ps;

	if (ac == 1 || ac == 2)
		return (0);
	ac -= 2;
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
	{
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	if (!create_reference_array(&ps))
		return (-1);
	size_t	i = 0;
	while (i < ps.a)
		ft_printf("%d\n", (ps.ref)[i++]);
	free(ps.ref);
	free_stack(&ps);
}
