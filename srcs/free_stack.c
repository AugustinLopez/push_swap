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
