#include <pushswap.h>

void	free_stack_elem(t_stack **elem)
{
	t_stack *tmp;

	if (*elem)
	{
		if ((*elem)->next)
			(*elem)->next->prev = (*elem)->prev;
		if ((*elem)->prev)
			(*elem)->prev->next = (*elem)->next;
		tmp = (*elem)->next;
		ft_memdel((void**)elem);
		*elem = tmp;
	}
}

int		squash_simple(t_pushswap *ps, int option1, int option2)
{
	t_stack	*elem;
	int		loop;

	loop = 0;
	elem = ps->instruction_begin;
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->val == option1 && elem->next->val == option2)
		{
			loop = 1;
			if (!elem->prev)
				ps->instruction_begin = elem->next->next;
			free_stack_elem(&elem);
			free_stack_elem(&elem);
		}
		if (elem)
			elem = elem->next;
	}
	return (loop);
}

int		squash_r(t_pushswap *ps, int option1, int option2, int option3)
{
	t_stack	*elem;
	t_stack	*first;
	int		loop;

	loop = 0;
	elem = ps->instruction_begin;
	first = 0;
	while (elem)
	{
		if (!elem->next)
			break ;
		if (!first && elem->val == option1)
			first = elem;
		else if (first && elem->val == option2)
		{
			first->val = option3;
			free_stack_elem(&elem);
			if (first->next && first->next->val == option1)
				first = first->next;
			else
				first = 0;
		}
		else
			first = 0;
		elem = elem->next;
	}
	return (loop);
}

int		squash_instruction(t_pushswap *ps)
{
	int		loop;
	t_stack	*elem;

	loop = 1;
	elem = ps->instruction_begin;
	if (!elem)
		return (0);
	while (loop)
	{
		loop = squash_simple(ps, SA, SA) + squash_simple(ps, SB, SB);
		loop += squash_simple(ps, RA, RRA) + squash_simple(ps, RB, RRB);
		loop += squash_simple(ps, RRA, RA) + squash_simple(ps, RRB, RB);
		loop += squash_simple(ps, PA, PB) + squash_simple(ps, PB, PA);
	}
	loop = 1;
	while (loop)
	{
		loop = squash_r(ps, SA, SB, SS) + squash_r(ps, SB, SA, SS);
		loop += squash_r(ps, RA, RB, RR) + squash_r(ps, RB, RA, RR);
		loop += squash_r(ps, RRA, RRB, RRR) + squash_r(ps, RRB, RRA, RRR);
	}
	return (0);
}
