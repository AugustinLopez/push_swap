# include <pushswap.h>

void	show_list(t_pushswap *ps, int option)
{
	t_stack *elem;

	if (option == 'a')
		elem = ps->top_a;
	else
		elem = ps->top_b;
	while (elem)
	{
		ft_printf("%c.%d\n",option, elem->val);
		elem = elem->prev;
	}
}

void	free_all_stack(t_pushswap *ps)
{
	t_stack	*stack;

	stack = ps->top_a;
	while (stack)
	{
		stack = stack->prev;
		free(ps->top_a);
		ps->top_a = stack;
	}
	stack = ps->top_b;
	while (stack)
	{
		stack = stack->prev;
		free(ps->top_b);
		ps->top_b = stack;
	}
	stack = ps->instruction_begin;
	while (stack)
	{
		stack = stack->next;
		free(ps->instruction_begin);
		ps->instruction_begin = stack;
	}
}

static int	ps_atoi(t_pushswap *ps, const char *src, int *result)
{
	char			sign;
	long			tmp;
	long			limit;

	(ps->a)++;
	tmp = 0;
	sign = 0;
	limit = INT_MAX;
	while ((*src >= 9 && *src <= 13) || *src == ' ')
		src++;
	if (*src == '+' || *src == '-')
		sign = (*(src++) == '+') ? 0 : 1;
	limit += sign;
	while ('0' <= *src && *src <= '9')
	{
		tmp = tmp * 10 + *(src++) - '0';
		if (tmp > limit)
			return (0);
	}
	if (*src)
		return (0);
	*result = sign ? tmp * -1 : tmp;
	return (1);
}

int	load_space_argv(t_pushswap *ps, char *av)
{
	char	**tmp;
	size_t	i;

	i = 0;

	if (!av)
		return (0);
	ft_printf("|%s|\n", av);
	tmp = ft_strsplit(av, ' ');
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		if (!ps_atoi(ps, tmp[i++], &(ps->top_a->next->val)))
			return (0);
		ps->top_a->next->prev = ps->top_a;
		ps->top_a = ps->top_a->next;
		ps->bot_b = ps->bot_a;
		while (ps->bot_b != ps->top_a)
		{
			if (ps->bot_b->val == ps->top_a->val)
				return (0);
			ps->bot_b = ps->bot_b->next;
		}
		(ps->a)++;
	}
	return (1);
}

int	load_initial_stack(t_pushswap *ps, char **av, int ac)
{
	if (!(ps->top_a = ft_memalloc(sizeof(t_stack)))
	|| !(ps_atoi(ps, av[ac], &(ps->top_a->val))))
		return (0);
	ps->bot_a = ps->top_a;
	while (ac--)
	{
		if (!(ps->top_a->next = ft_memalloc(sizeof(t_stack))))
			return (0);
		ps->top_a->next->prev = ps->top_a;
		ps->top_a = ps->top_a->next;
		if (!(ps_atoi(ps, av[ac], &(ps->top_a->val))))
			return (0);
		ps->bot_b = ps->bot_a;
		while (ps->bot_b != ps->top_a)
		{
			if (ps->bot_b->val == ps->top_a->val)
				return (0);
			ps->bot_b = ps->bot_b->next;
		}
	}
	ps->bot_b = NULL;
	return (1);
}

int	load_instruction_stack(t_pushswap *ps, int instruction)
{
	t_stack	*elem;

	if (!(ps->instruction_begin))
	{
		if (!(ps->instruction_begin = ft_memalloc(sizeof(t_stack))))
			return (0);
		ps->instruction_begin->val = instruction;
		ps->instruction_end = ps->instruction_begin;
	}
	else
	{
		if (!(elem = ft_memalloc(sizeof(t_stack))))
			return (0);
		elem->val = instruction;
		elem->prev = ps->instruction_end;
		ps->instruction_end->next = elem;
		ps->instruction_end = elem;
	}
	return (1);
}
