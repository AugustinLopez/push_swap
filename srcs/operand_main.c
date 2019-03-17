# include <pushswap.h>
# include <libft.h>

void		ps_operand(t_pushswap *ps, int option, int affichage)
{
	if (option == SA || option == SB || option == SS)
		ps_swap(ps, option);
	else if (option == PA || option == PB)
		ps_push(ps, option);
	else if (option == RA || option == RB || option == RR)
		ps_rotate(ps, option);
	else if (option == RRA || option == RRB || option == RRR)
		ps_reverse_rotate(ps, option);
	if (affichage)
		load_instruction_stack(ps, option);
}
