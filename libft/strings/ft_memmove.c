/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:09:16 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:55:41 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* check if two memory has overlap pointer address */

static int	has_overlap(void const *m1, void const *m2)
{
	if (m1 > m2)
		return (1);
	return (0);
}

/*
	Copy overlapped memory
*/

static void	*ft_mem_cpy_overlap(void *dest, void const *src, size_t n)
{
	unsigned char	*d_clone;
	unsigned char	*s_clone;

	d_clone = (unsigned char *)dest;
	s_clone = (unsigned char *)src;
	while (n > 0)
	{
		n--;
		d_clone[n] = s_clone[n];
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (NULL);
	if (n == 0)
		return (dest);
	if (has_overlap(dest, src))
		return (ft_mem_cpy_overlap(dest, src, n));
	else
		return (ft_memcpy(dest, src, n));
	return (NULL);
}
