/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:40:02 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:54:51 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_same(unsigned char c1, unsigned char c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_clone;
	unsigned char	*s2_clone;

	if (n == 0)
		return (0);
	s1_clone = (unsigned char *)s1;
	s2_clone = (unsigned char *)s2;
	i = 0;
	while (i < n - 1 && is_same(s1_clone[i], s2_clone[i]))
		i++;
	if (i < n)
		return (s1_clone[i] - s2_clone[i]);
	return (0);
}
