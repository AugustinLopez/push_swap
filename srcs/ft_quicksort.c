/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:16:23 by aulopez           #+#    #+#             */
/*   Updated: 2019/04/11 16:16:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

static void	qs_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	qs_partition(int **array, int first, int last)
{
	int pivot;
	int low;
	int i;

	pivot = (*array)[last];
	low = first;
	i = first;
	while (i < last)
	{
		if ((*array)[i] < pivot)
			qs_swap(&((*array)[i]), &((*array)[low++]));
		i++;
	}
	qs_swap(&((*array)[last]), &((*array)[low]));
	return (low);
}

void		ft_quicksort(int **array, int first, int last)
{
	int	pivot;

	if (first < last)
	{
		pivot = qs_partition(array, first, last);
		ft_quicksort(array, first, pivot - 1);
		ft_quicksort(array, pivot + 1, last);
	}
}

int			get_pivot(int option, t_pushswap *ps, size_t len, size_t *error)
{
	int		*tab;
	int		i;
	size_t	size;
	t_stack	*elem;

	*error = 0;
	i = 0;
	elem = (option == 'a') ? ps->top_a : ps->top_b;
	tab = (int *)malloc(sizeof(int) * len);
	if (tab)
	{
		size = 0;
		while (elem && len--)
		{
			tab[size++] = elem->val;
			elem = elem->prev;
		}
		ft_quicksort(&tab, 0, size - 1);
		i = tab[size / 2];
		free(tab);
	}
	else
		*error = 1;
	return (i);
}
