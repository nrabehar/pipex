/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:58:34 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:55:57 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
fills the first n bytes of the memory area pointed to by s with the constant
byte c.
returns a pointer to the memory area s.
*/

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_clone;

	s_clone = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_clone[i] = (unsigned char)c;
		i++;
	}
	return (s_clone);
}
