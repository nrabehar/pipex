/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:32:08 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:55:36 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d_clone;
	unsigned char	*s_clone;

	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	i = 0;
	d_clone = (unsigned char *)dest;
	s_clone = (unsigned char *)src;
	while (i < n)
	{
		d_clone[i] = s_clone[i];
		i++;
	}
	return (d_clone);
}
