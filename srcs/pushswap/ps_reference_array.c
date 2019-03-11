# include <pushswap.h>

static void	qs_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		qs_partition(int **array, int first, int last)
{
	int pivot;
	int low;
	int i;

	pivot = (*array)[last];
	low = first;
	i = first;
	while (i <= last - 1)
	{
		if ((*array)[i] < pivot)
			qs_swap(&((*array)[i]), &((*array)[low++]));
		i++;
	}
	qs_swap(&((*array)[last]), &((*array)[low]));
	return (low);
}

static void	qs_quicksort_array(int **array, int first, int last)
{
	int	pivot;

	if (first < last)
	{
		pivot = qs_partition(array, first, last);
		qs_quicksort_array(array, first, pivot - 1);
		qs_quicksort_array(array, pivot + 1, last);
	}
}

int		create_reference_array(t_pushswap *ps)
{
	size_t	i;

	if (!(ps->ref = ft_memalloc(sizeof(int) * ps->a)))
	{
		ft_putendl_fd("Not enough memory", 2);
		return (0);
	}
	ps->top_b = ps->top_a;
	i = 0;
	while (ps->top_b)
	{
		(ps->ref)[i++] = (ps->top_b)->val;
		ps->top_b = (ps->top_b)->prev;
	}
	qs_quicksort_array(&(ps->ref), 0, ps->a - 1);
	ps->top_b = 0;
	return (1);
}
