# include <pushswap.h>

void	free_stack(t_pushswap *ps)
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
}

static int	ps_atoi(const char *src, int *result)
{
	char			sign;
	long			tmp;
	long			limit;

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

int	load_initial_stack(t_pushswap *ps, char **av, int ac)
{
	if (!(ps->bot_a = ft_memalloc(sizeof(t_stack)))
	|| !(ps_atoi(av[ac], &(ps->bot_a->val))))
		return (0);
	ps->top_a = ps->bot_a;
	ps->a = 1;
	while (ac--)
	{
		if (!(ps->top_a->next = ft_memalloc(sizeof(t_stack)))
		|| !(ps_atoi(av[ac], &(ps->top_a->next->val))))
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
	ps->bot_b = NULL;
	return (1);
}
