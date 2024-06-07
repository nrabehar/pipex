/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:21:35 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_issamechar(unsigned char c1, unsigned char c2)
{
	if (!c1 || !c2)
		return (0);
	if (c1 == c2)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_clone;
	unsigned char	*s2_clone;

	i = 0;
	s1_clone = (unsigned char *)s1;
	s2_clone = (unsigned char *)s2;
	while (i < n && ft_issamechar(s1_clone[i], s2_clone[i]))
		i++;
	if (i < n)
		return (s1_clone[i] - s2_clone[i]);
	return (0);
}
