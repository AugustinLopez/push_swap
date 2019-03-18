# include <pushswap.h>

int			checker_operand(char buf[5])
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

int			checker_clean_stdout(void)
{
	char	buf[4096 + 1];
	int		ret;

	while ((ret = read(0, &buf, 4096)) && ret > 0)
	{
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n'))
			break;
	}
	return (-1);
}

int			checker_gnl(void)
{
	char		buf[4];
	char		c;
	int			ret;
	int			read_once;

	read_once = 0;
	if ((ret = read(0, buf, 3)) && ret > 2)
	{
		buf[3] = '\0';
		read_once = (buf[2] != '\n') ? 1 : 0;
		(buf[2] == '\n') ? buf[2] = 0 : 0;
		if (buf[0] == '\n' || buf[1] == '\n')
			return (-1);
	}
	if (!ret)
		return (0);
	else if (ret < 3)
		return (-1);
	c = '\n';
	ret = read_once ? read(0, &c, 1) : 1;
	if (ret <= 0 || c != '\n')
		return (checker_clean_stdout());
	return (checker_operand(buf));
}

static int	checker_is_it_sorted(t_pushswap *ps)
{
	t_stack *stack;

	if (ps->bot_b)
	{
		ft_putendl("KO");
		return (-1);
	}
	stack = ps->top_a;
	while (stack)
	{
		if (stack->prev && stack->val > stack->prev->val)
		{
			ft_putendl("KO");
			return (-1);
		}
		stack = stack->prev;
	}
	ft_putendl("OK");
	return (0);
}

int	main(int ac, char **av)
{
	t_pushswap	ps;
	int			operand;

	if (ac < 2)
		return (0);
	ac -= 2;
	av++;
	ft_bzero(&ps, sizeof(ps));
	if (!(load_initial_stack(&ps, av, ac)))
	{
		free_all_stack(&ps);
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	while ((operand = checker_gnl()))
	{
		if (operand == -1)
		{
			ft_putendl_fd("Error", 2);
			return (-1);
		}
		ps_operand(&ps, operand, 0);
	}
	show_list(&ps, 'a');
	checker_is_it_sorted(&ps);
	free_all_stack(&ps);
	return (0);
}
