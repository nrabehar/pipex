/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:35:44 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:54:56 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_same(unsigned char const c1, unsigned char const c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

/*
scans the initial `n` bytes of the memory area pointed to by `s` for the first
instance of `c`.
return a pointer to the matching byte or `NULL` if the character
does not occur in the given memory area.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_clone;

	i = 0;
	s_clone = (unsigned char *)s;
	while (i < n)
	{
		if (is_same(s_clone[i], c))
			return (&s_clone[i]);
		i++;
	}
	return (NULL);
}
