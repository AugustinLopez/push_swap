/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:37:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/19 14:25:18 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

void				free_data_stack(t_pushswap *ps)
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

inline static int	ps_atoi(t_pushswap *ps, const char *src, int *result)
{
	char			sign;
	long			tmp;
	long			limit;

	(ps->a)++;
	tmp = 0;
	sign = 0;
	limit = INT_MAX;
	while ((*src >= 9 && *src <= 13) || *src == ' ')
		src++;
	if (*src == '+' || *src == '-')
		sign = (*(src++) == '+') ? 0 : 1;
	limit += sign;
	while ('0' <= *src && *src <= '9')
	{
		tmp = tmp * 10 + *(src++) - '0';
		if (tmp > limit)
			return (0);
	}
	if (*src)
		return (0);
	*result = sign ? tmp * -1 : tmp;
	return (1);
}

inline static int	load_number(t_pushswap *ps, char *tmp)
{
	if (!ps_atoi(ps, tmp, &(ps->bot_a->val)))
		return (0);
	ps->bot_b = ps->top_a;
	while (ps->bot_b != ps->bot_a)
	{
		if (ps->bot_b->val == ps->bot_a->val)
			return (0);
		ps->bot_b = ps->bot_b->prev;
	}
	return (1);
}

inline static int	load_space_argv(t_pushswap *ps, char **tmp)
{
	size_t	i;

	i = 0;
	while (tmp[i])
	{
		if (!(ps->bot_a))
		{
			if (!(ps->bot_a = ft_memalloc(sizeof(t_stack))))
				return (0);
			ps->top_a = ps->bot_a;
		}
		else
		{
			if (!(ps->bot_a->prev = ft_memalloc(sizeof(t_stack))))
				return (0);
			ps->bot_a->prev->next = ps->bot_a;
			ps->bot_a = ps->bot_a->prev;
		}
		if (!(load_number(ps, tmp[i++])))
			return (0);
	}
	return (1);
}

int					load_initial_stack(t_pushswap *ps, char **av, int ac)
{
	int		i;
	char	**tmp;

	i = -1;
	while (++i < ac)
	{
		tmp = ft_strsplit(av[i], ' ');
		i = (!tmp || load_space_argv(ps, tmp)) ? i : -1;
		ft_free_sarray(&tmp);
		if (i == -1)
			return (0);
	}
	ps->bot_b = NULL;
	return (1);
}
