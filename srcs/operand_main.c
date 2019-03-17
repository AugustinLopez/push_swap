# include <pushswap.h>
# include <libft.h>

void		ps_operand(t_pushswap *ps, int option, t_list **instruction)
{
	t_list	*new;

	if (option == SA || option == SB || option == SS)
		ps_swap(ps, option);
	else if (option == PA || option == PB)
		ps_push(ps, option);
	else if (option == RA || option == RB || option == RR)
		ps_rotate(ps, option);
	else if (option == RRA || option == RRB || option == RRR)
		ps_reverse_rotate(ps, option);
	if (instruction)
	{
		new = ft_lstnew(0,0);
		//need to protect mem alloc
		new->zu = option;
		(*instruction)->next = new;
		(*instruction) = (*instruction)->next;
	}
}
