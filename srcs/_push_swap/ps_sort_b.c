#include <pushswap.h>

//memory need to be monitored. ps_operand should return 0 or -1

int		sort_onplace_b(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	z = (len == 3) ? ps->top_b->prev->prev->val : 0;
	if (x < y && y < z)
	{
		ps_operand(ps, SB, 1);
		ps_operand(ps, RRB, 1);
	}
	else if (x < z && z < y)
		ps_operand(ps, RB, 1);
	else if (z < x && x < y)
		ps_operand(ps, SB, 1);
	else if (y < z && z < x)
	{
		ps_operand(ps, RRB, 1);
		ps_operand(ps, SB, 1);
	}
	else if (y < x && x < z)
		ps_operand(ps, RRB, 1);
	return (0);
}

int		sort_notonplace_b(t_pushswap *ps, size_t len)
{
	while (--len)
	{
		if (ps->top_b->val < ps->top_b->prev->val)
		{
			ps_operand(ps, SB, 1);
			ps_operand(ps, RB, 1);
		}
		else
			ps_operand(ps, RB, 1);
	}
	while (++len < 3)
	{
		ps_operand(ps, RRB, 1);
		if (ps->top_b->val < ps->top_b->prev->val)
			ps_operand(ps, SB, 1);
	}
	if (ps->top_b && ps->top_b->val < ps->top_b->prev->val)
		ps_operand(ps, SB, 1);
	return (0);
}

int		sort_little_b(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;

	x = ps->top_b->val;
	y = (len >= 2) ? ps->top_b->prev->val : 0;
	if (len == 1)
		return (0);
	else if (len == 2 && x < y)
		ps_operand(ps, SB, 1);
	else if (ps->b == 3 && len == 3)
		sort_onplace_b(ps, len);
	else if (len == 3)
		sort_notonplace_b(ps, len);
	return (0);
}
