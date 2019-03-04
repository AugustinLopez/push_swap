#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <libft.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

enum {ERROR = -1, END = 0, SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR};

/*
** Using two array t[argc] might be more efficient.
** But it won't affect the number of operation, so it is irrelevant.
*/

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
	int				max_a;
	int				min_a;
	size_t			a;
	size_t			b;
}					t_pushswap;

void				ps_swap(t_pushswap *ps, int option);
void				ps_push(t_pushswap *ps, int option);
void				ps_rotate(t_pushswap *ps, int option);
void				ps_reverse_rotate(t_pushswap *ps, int option);
void				ps_operand(t_pushswap *ps, int option);

int					ps_atoi(const char *src, int *result);
int					load_initial_stack(t_pushswap *ps, char **av, int ac);
void				free_stack(t_pushswap *ps);

#endif
