#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <libft.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# define SA 1
# define SB 2
# define PA 3
# define PB 4
# define RA 5
# define RB 6
# define RRA 7
# define RRB 8
# define SS 9
# define RR 10
# define RRR 11

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
	t_stack			*instruction_begin;
	t_stack			*instruction_end;
	int				stop;
	size_t			a;
	size_t			b;
}					t_pushswap;

void				ps_swap(t_pushswap *ps, int option);
void				ps_push(t_pushswap *ps, int option);
void				ps_rotate(t_pushswap *ps, int option);
void				ps_reverse_rotate(t_pushswap *ps, int option);
void				ps_operand(t_pushswap *ps, int option, int affichage);
void				ps_several_operand(t_pushswap *ps, int option);

int					sort_little_a(t_pushswap *ps, size_t len);
int					sort_little_b(t_pushswap *ps, size_t len);
int					sort_stack_a(t_pushswap *ps, size_t len);

int					squash_instruction(t_pushswap *ps);
void				show_list(t_pushswap *ps, int option);
int					load_initial_stack(t_pushswap *ps, char **av, int ac);
int					load_instruction_stack(t_pushswap *ps, int instruction);
void				free_all_stack(t_pushswap *ps);
int					get_pivot(int option, t_pushswap *ps, size_t len);
#endif
