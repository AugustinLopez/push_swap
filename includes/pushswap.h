/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:00:52 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/10 12:41:31 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

/*
** -- Headers ------------------------------------------------------------------
*/

/*
** stdlib for free and malloc
** limits for INT_MAX and INT_MIN: more convenient
** unitsd for write, read
** time for usleep (bonus)
*/

# include <libft.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <time.h>

/*
** --- Define ------------------------------------------------------------------
*/

/*
** SA to RRR are value attributed to operation.
** SA to RRB needs to be between 1 and 8 (function ps_several_operand)
** CH_V to CH_D are checkers flags : visualize, color, slow, fast, instant, data
** Their value needs to be a power of 2 (function ch_available_option)
*/

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

# define CH_V 1
# define CH_C 2
# define CH_S 4
# define CH_F 8
# define CH_I 16
# define CH_D 32
# define CH_H 64

/*
** --- Structures --------------------------------------------------------------
*/

/*
** t_stack is a double-link list
** s_pushswap contains pointers to the end and beginning of both stack plus a
** stack of instructions (easier to modify, see squash_operand_stack).
** a and b are the current size of the stack.
*/

typedef struct		s_stack
{
	struct s_stack	*prev;
	struct s_stack	*next;
	int				val;
	unsigned int	index;
}					t_stack;

typedef struct		s_move
{
	size_t			ra;
	size_t			rb;
	size_t			rra;
	size_t			rrb;
	size_t			real;
	size_t			i;
}					t_move;

typedef struct		s_visualize
{
	t_stack			*a;
	t_stack			*b;
	size_t			total;
	size_t			offset;
	int				flags;
	char			*oper;
}					t_visualize;

typedef struct		s_pushswap
{
	t_stack			*bot_a;
	t_stack			*bot_b;
	t_stack			*top_a;
	t_stack			*top_b;
	t_stack			*instruction_begin;
	t_stack			*instruction_end;
	size_t			a;
	size_t			b;
	int				max;
	int				min;
}					t_pushswap;

/*
** --- Functions --------------------------------------------------------------
*/

/*
** Operand.
*/

void				ps_swap(t_pushswap *ps, int option);
void				ps_push(t_pushswap *ps, int option);
void				ps_rotate(t_pushswap *ps, int option);
void				ps_reverse_rotate(t_pushswap *ps, int option);
int					ps_operand(t_pushswap *ps, int option, int affichage);
int					ps_several_operand(t_pushswap *ps, int option);
int					load_operand_stack(t_pushswap *ps, int instruction);
int					squash_operand_stack(t_pushswap *ps);

/*
** Sort.
*/

int					backtrack_stack(int option, t_pushswap *p, size_t rr);
int					other_push_needed(int option, t_pushswap *ps,
										size_t len, int pivot);
int					sort_little_a(t_pushswap *ps, size_t len);
int					sort_little_b(t_pushswap *ps, size_t len);
int					sort_stack_a(t_pushswap *ps, size_t len);
int					get_pivot(int option, t_pushswap *ps,
								size_t len, size_t *error);
int					is_it_sorted(t_pushswap *ps, int option);
void				ft_quicksort(int **array, int first, int last);
int					define_index(t_pushswap *ps);
size_t				find_max_index(int option, t_pushswap *ps);
size_t				find_min_index(int option, t_pushswap *ps);
t_stack				*find_elem_index(int option, t_pushswap *ps, size_t index);
size_t				mode_incremental(t_pushswap *ps, size_t index);
size_t				mode_greater(t_pushswap *ps, size_t index);
int					sort_by_step(t_pushswap *ps, size_t (*mode)(t_pushswap *, size_t));
int					sort_step1(t_pushswap *ps, size_t best_index, size_t (*mode)(t_pushswap *, size_t));
int					sort_step2(t_pushswap *ps);

/*
** Initialization & Free.
*/

int					load_initial_stack(t_pushswap *ps, char **av, int ac);
void				find_max_min(t_stack *elem, int *max, int *min);
void				free_data_stack(t_pushswap *ps);
void				free_instruction_stack(t_pushswap *ps);
void				stackdelone(t_stack **elem);
void				stackdel(t_stack **elem);
int					ret_error(t_pushswap *ps);

/*
** Checker.
*/

int					ch_gnl(t_pushswap *ps, char *line, int flags);
int					ch_parsing(int ac, char **av, int *flags);
void				ch_visualize(t_pushswap *ps, int flags, char *oper);
#endif
