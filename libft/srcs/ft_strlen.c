/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:29:13 by aulopez           #+#    #+#             */
/*   Updated: 2019/02/22 12:27:30 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

inline static const char	*find_null_byte(const unsigned long *longword_ptr,
											unsigned long lomagic,
											unsigned long himagic)
{
	unsigned long			longword;
	const char				*cp;
	int						i;

	while (1)
	{
		longword = *longword_ptr++;
		if (((longword - lomagic) & ~longword & himagic))
		{
			i = 0;
			cp = (const char *)(longword_ptr - 1);
			while (i < 4)
			{
				if (!cp[i])
					return (cp + i);
				++i;
			}
			if (sizeof(longword) > 4)
				while (i < 8)
					if (!cp[i++])
						return (cp + i - 1);
		}
	}
}

/*
** The first loop read characters until memory is aligned properly.
** himagic and lomagic are bitmask used to catch the first '/0'
** the sizeof > 4 is for 64 bits system.
** 		shift in two step to avoid warning on 32 bits
*/

size_t						ft_strlen(const char *s)
{
	const char				*char_ptr;
	const unsigned long		*longword_ptr;
	unsigned long			himagic;
	unsigned long			lomagic;

	char_ptr = s;
	while ((unsigned long)char_ptr & (sizeof(unsigned long) - 1))
		if (!(*char_ptr++))
			return (char_ptr - s - 1);
	longword_ptr = (unsigned long *)char_ptr;
	himagic = 0x80808080L;
	lomagic = 0x01010101L;
	if (sizeof(unsigned long) > 4)
	{
		himagic = ((himagic << 16) << 16) | himagic;
		lomagic = ((lomagic << 16) << 16) | lomagic;
	}
	return (find_null_byte(longword_ptr, lomagic, himagic) - s);
}
