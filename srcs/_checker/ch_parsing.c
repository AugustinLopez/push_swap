/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:47:48 by aulopez           #+#    #+#             */
/*   Updated: 2019/03/25 14:38:10 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pushswap.h>

inline static int	ch_operand(char *buf)
{
	if (!ft_strcmp(buf, "sa"))
		return (SA);
	if (!ft_strcmp(buf, "sb"))
		return (SB);
	if (!ft_strcmp(buf, "ss"))
		return (SS);
	if (!ft_strcmp(buf, "pa"))
		return (PA);
	if (!ft_strcmp(buf, "pb"))
		return (PB);
	if (!ft_strcmp(buf, "ra"))
		return (RA);
	if (!ft_strcmp(buf, "rb"))
		return (RB);
	if (!ft_strcmp(buf, "rr"))
		return (RR);
	if (!ft_strcmp(buf, "rra"))
		return (RRA);
	if (!ft_strcmp(buf, "rrb"))
		return (RRB);
	if (!ft_strcmp(buf, "rrr"))
		return (RRR);
	return (-1);
}

int					ch_gnl(t_pushswap *ps, char *line, int flags)
{
	size_t	size;
	int		i;

	size = ft_strlen(line);
	if (3 > size || size > 4)
		return (-1);
	line[size - 1] = '\0';
	i = ch_operand(line);
	if (i != -1)
	{
		ps_operand(ps, i, 0);
		ch_visualize(ps, flags, line);
	}
	free(line);
	return (i);
}

inline static int	ch_available_option(char *av, int *flags)
{
	int	i;

	while (*(++av))
	{
		if (!(i = ft_strchri("vcsfidh", av[0])))
			return (0);
		*flags |= (1 << (i - 1));
	}
	return (1);
}

int					ch_parsing(int ac, char **av, int *flags)
{
	int	i;

	i = 0;
	*flags = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-' && !av[i][2])
			return (i + 1);
		if (av[i][0] == '-' && ('0' <= av[i][1] && av[i][1] <= '9'))
			return (i);
		if (!ch_available_option(av[i], flags))
			return (0);
	}
	if (*flags & (CH_C | CH_S | CH_F | CH_I))
		*flags |= CH_V;
	return (i);
}
