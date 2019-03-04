# include <pushswap.h>

void	ps_rotate(t_pushswap *ps, int option)
{
	if (option == RA || option == RR)
	{
		if (ps->top_a && ps->top_a != ps->bot_a)
		{
			ps->top_a->next = ps->bot_a;
			ps->bot_a->prev = ps->top_a;
			ps->bot_a = ps->bot_a->prev;
			ps->top_a = ps->top_a->prev;
			ps->top_a->next = NULL;
			ps->bot_a->prev = NULL;
		}
	}
	if (option == RB || option == RR)
	{
		if (ps->top_b && ps->top_b != ps->bot_b)
		{
			ps->top_b->next = ps->bot_b;
			ps->bot_b->prev = ps->top_b;
			ps->bot_b = ps->bot_b->prev;
			ps->top_b = ps->top_b->prev;
			ps->top_b->next = NULL;
			ps->bot_b->prev = NULL;
		}
	}
}

void	ps_reverse_rotate(t_pushswap *ps, int option)
{
	if (option == RRA || option == RRR)
	{
		if (ps->bot_a && ps->top_a != ps->bot_a)
		{
			ps->bot_a->prev = ps->top_a;
			ps->top_a->next = ps->bot_a;
			ps->top_a = ps->top_a->next;
			ps->bot_a = ps->bot_a->next;
			ps->bot_a->prev = NULL;
			ps->top_a->next = NULL;
		}
	}
	if (option == RB || option == RRR)
	{
		if (ps->bot_b && ps->top_b != ps->bot_b)
		{
			ps->bot_b->prev = ps->top_b;
			ps->top_b->next = ps->bot_b;
			ps->top_b = ps->top_b->next;
			ps->bot_b = ps->bot_b->next;
			ps->bot_b->prev = NULL;
			ps->top_b->next = NULL;
		}
	}
}

void	ps_swap(t_pushswap *ps, int option)
{
	int	tmp;

	if (option == SA || option == SS)
	{
		if (ps->top_a && ps->top_a->prev)
		{
			tmp = ps->top_a->val;
			ps->top_a->val = ps->top_a->prev->val;
			ps->top_a->prev->val = tmp;
		}
	}
	if (option == SB || option == SS)
	{
		if (ps->top_b && ps->top_b->prev)
		{
			tmp = ps->top_b->val;
			ps->top_b->val = ps->top_b->prev->val;
			ps->top_b->prev->val = tmp;
		}
	}
}
