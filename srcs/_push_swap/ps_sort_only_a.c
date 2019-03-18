#include <pushswap.h>

//memory need to be monitored. ps_operand should return 0 or -1

int		sort_onplace_a(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;
	int	z;

	x = ps->top_a->val;
	y = (len >= 2) ? ps->top_a->prev->val : 0;
	z = (len == 3) ? ps->top_a->prev->prev->val : 0;
	if (x > y && y > z)
	{
		ps_operand(ps, SA, 1);
		ps_operand(ps, RRA, 1);
	}
	else if (x > z && z > y)
		ps_operand(ps, RA, 1);
	else if (z > x && x > y)
		ps_operand(ps, SA, 1);
	else if (y > z && z > x)
	{
		ps_operand(ps, RRA, 1);
		ps_operand(ps, SA, 1);
	
	}
	else if (y > x && x > z)
		ps_operand(ps, RRA, 1);
	return (0);
}

int		sort_notonplace_a(t_pushswap *ps, size_t len)
{
	while (len-- > 1)
	{
		if (ps->top_a->val > ps->top_a->prev->val)
		{
			ps_operand(ps, SA, 1);
			ps_operand(ps, RA, 1);
		}
		else
			ps_operand(ps, RA, 1);
	}
	while (++len < 3)
	{
		ps_operand(ps, RRA, 1);
		if (ps->top_a && ps->top_a->val > ps->top_a->prev->val)
			ps_operand(ps, SA, 1);
	}
	if (ps->top_a && ps->top_a->val > ps->top_a->prev->val)
		ps_operand(ps, SA, 1);
	return (0);
}

int		sort_little_a(t_pushswap *ps, size_t len)
{
	int	x;
	int	y;

	x = ps->top_a->val;
	y = (len >= 2) ? ps->top_a->prev->val : 0;
	if (len == 1)
		return (0);
	else if (len == 2 && x > y)
		ps_operand(ps, SA, 1);
	else if (ps->a == 3 && len == 3)
		sort_onplace_a(ps, len);
	else if (len == 3)
		sort_notonplace_a(ps, len);
	return (0);
}
