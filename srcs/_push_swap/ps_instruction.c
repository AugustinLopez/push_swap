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

int		squash_jump(t_pushswap *ps, int option1, int option2, int jump)
{
	t_stack	*elem;
	t_stack *tmp;
	int		loop;

	loop = 0;
	elem = ps->instruction_begin;
	while (elem)
	{
		if (!elem->next)
			break ;
		if (elem->val == option1)
		{
			tmp = elem->next;
			while (tmp->val == jump)
				tmp = tmp->next;
			if (tmp->val == option2)
			{
				loop = 1;
				if (!elem->prev)
					ps->instruction_begin = elem->next;
				if (ps->instruction_begin == tmp)
					ps->instruction_begin = elem->next;
				free_stack_elem(&elem);
				free_stack_elem(&tmp);
			}
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

int		squash_r_jump(t_pushswap *ps, int option1, int option2, int jump)
{
	t_stack	*elem;
	t_stack	*first;
	int		loop;
	int		option3;

	option3 = SS * (option1 == SA || option2 == SA);
	option3 += RR * (option1 == RA || option2 == RA);
	option3 += RRR * (option1 == RRA || option2 == RRA);
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
		else if (elem->val != jump)
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
		loop = squash_jump(ps, SA, SA, RB) + squash_jump(ps, SB, SB, RA);
		loop += squash_jump(ps, SA, SA, RRB) + squash_jump(ps, SB, SB, RRA);
		loop += squash_jump(ps, RA, RRA, SB) + squash_jump(ps, RB, RRB, SA);
		loop += squash_jump(ps, RRA, RA, SB) + squash_jump(ps, RRB, RB, SA);
		loop += squash_simple(ps, PA, PB) + squash_simple(ps, PB, PA);
	}
	loop = 1;
	while (loop)
	{
		loop = squash_r_jump(ps, SA, SB, RA) + squash_r_jump(ps, SB, SA, RB);
		loop += squash_r_jump(ps, SA, SB, RRA) + squash_r_jump(ps, SB, SA, RRB);
		loop += squash_r_jump(ps, RA, RB, SA) + squash_r_jump(ps, RB, RA, SB);
		loop += squash_r_jump(ps, RRA, RRB, SA) + squash_r_jump(ps, RRB, RRA, SB);
	}
	return (0);
}
