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

/*int			checker_gnl(char *line)
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
*/

int	checker_gnl(char *line)
{
	size_t	size;

	size = ft_strlen(line);
	if (3 > size || size > 4)
		return (-1);
	line[size - 1] = '\0';
	return (checker_operand(line));
}

void	visualize(t_pushswap *ps, int option)
{
	t_stack	*elem;

	elem = (option == 'a') ? ps->top_a : ps->top_b;
	ft_printf("\n%c:", option - 32);
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
}

/*
** possible optimisation : SA RA SB - SB RB SA --> SS RA | SS RB
*/

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
	{
		free_all_stack(&ps);
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	visualize(&ps, 'a');
	visualize(&ps, 'b');
	ft_putchar('\n');
	while ((operand = ft_gnl(0, &line, 1)) > 0)
	{
		//ft_printf("|%s\n|", line);
		operand = checker_gnl(line);
		free(line);
		if (operand == -1)
			break ;
		ps_operand(&ps, operand, 0);
		visualize(&ps, 'a');
		visualize(&ps, 'b');
		ft_putchar('\n');
		/*operand = checker_gnl(line);
		if (operand == 1)
		{
			free_all_stack(&ps);
			ft_putendl_fd("Error", 2);
			return (-1);
		}
		free(line);
		ps_operand(&ps, operand, 0);*/
	}
		ft_putchar('\n');

	if (operand == -1)
	{
		free_all_stack(&ps);
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	//show_list(&ps, 'a');
	checker_is_it_sorted(&ps);
	free_all_stack(&ps);
	return (0);
}
