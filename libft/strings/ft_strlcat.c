/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:25:47 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:54:10 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	max_len;
	size_t	i;

	if (!dst && !size)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	max_len = size - dst_len - 1;
	if (size <= dst_len)
		return (src_len + size);
	i = 0;
	while (src && i < max_len && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
