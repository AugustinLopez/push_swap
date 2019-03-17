#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <libft.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

enum {ERROR = -1, END = 0, JUMP, SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};

typedef struct		s_stack
{
	struct s_stack	*prev;
	struct s_stack	*next;
	int				val;
}					t_stack;

typedef struct		s_pushswap
{
	t_stack			*bot_a;
	t_stack			*bot_b;
	t_stack			*top_a;
	t_stack			*top_b;
	size_t			a;
	size_t			b;
}					t_pushswap;

typedef struct		s_sorting
{
	int				*array;
	size_t			s;
	int				pivot;
	t_list			*begin;
	t_list			*end;
}					t_sorting;

void				ps_swap(t_pushswap *ps, int option);
void				ps_push(t_pushswap *ps, int option);
void				ps_rotate(t_pushswap *ps, int option);
void				ps_reverse_rotate(t_pushswap *ps, int option);
void				ps_operand(t_pushswap *ps, int option, t_list **instruction);
int					sort_little_a(t_pushswap *ps, t_sorting *st, size_t len);
int					sort_little_b(t_pushswap *ps, t_sorting *st, size_t len);
int					sort_stack_a(t_pushswap *ps, t_sorting *st, size_t len);
int					sort_stack_b(t_pushswap *ps, t_sorting *st, size_t len);
int					load_initial_stack(t_pushswap *ps, char **av, int ac);
void				free_stack(t_pushswap *ps);
int					create_reference_array(t_pushswap *ps, t_sorting *st);
void	qs_quicksort_array(int **array, int first, int last);
#endif
