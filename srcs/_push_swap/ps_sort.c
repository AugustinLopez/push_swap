# include <pushswap.h>

static int	other_push_needed(int option, t_pushswap *ps, size_t len, int pivot)
{
	t_stack	*elem;

	elem = option == 'a' ? ps->top_a : ps->top_b;
	while (len--)
	{
		if ((option == 'a' && elem->val < pivot)
			|| (option == 'b' && elem->val > pivot))
			return (1);
		elem = elem->prev;
	}
	return (0);
}

static int	backtrack_stack(int option, t_pushswap *ps, size_t rr)
{
	if (option == 'a')
	{
		if (rr > ps->a / 2)
			while (ps->a - rr++)
				ps_operand(ps, RA, 1);
		else
			while (rr--)
				ps_operand(ps, RRA, 1);
	}
	else if (option == 'b')
	{
		if (rr > ps->b / 2)
			while (ps->b - rr++)
				ps_operand(ps, RB, 1);
		else
			while (rr--)
				ps_operand(ps, RRB, 1);
	}
	return (0);
}

static int	sort_stack_b(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	rb;
	size_t	pa;
	size_t	i;

	rb = 0;
	pa = 0;
	i = 0;
	if (len <= 3)// || (len == 4 && ps->b == 4))
		return (sort_little_b(ps, len));
	pivot = get_pivot('b', ps, len);
	while (other_push_needed('b', ps, len - i, pivot) && i++ < len)
	{
		if (ps->top_b->val > pivot)
		{
			pa++;
			ps_operand(ps, PA, 1);
		}
		else
		{
			rb++;
			ps_operand(ps, RB, 1);
		}
	}
	sort_stack_a(ps, pa);
	backtrack_stack('b', ps, rb);
	sort_stack_b(ps, len - pa);
	while (pa--)
		ps_operand(ps, PB, 1);
	return (0);
}

int			sort_stack_a(t_pushswap *ps, size_t len)
{
	int		pivot;
	size_t	ra;
	size_t	pb;
	size_t	i;

	ra = 0;
	pb = 0;
	i = 0;
	if (len <= 3)// || (len == 4 && ps->a == 4))
		return (sort_little_a(ps, len));
	pivot = get_pivot('a', ps, len);
	while (other_push_needed('a', ps, len - i, pivot) && i++ < len)
	{
		if (ps->top_a->val < pivot)
		{
			pb++;
			ps_operand(ps, PB, 1);
		}
		else
		{
			ra++;
			ps_operand(ps, RA, 1);
		}
	}
	backtrack_stack('a', ps, ra);
	sort_stack_a(ps, len - pb);
	sort_stack_b(ps, pb);
	while (pb--)
		ps_operand(ps, PA, 1);
	return (0);
}
