/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:00:05 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/09 00:30:14 by nrabehar         ###   ########.fr       */
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

int	ft_strnrcmp(const char *s1, const char *s2, size_t n)
{
	size_t			s1_len;
	size_t			s2_len;
	unsigned char	*s1_clone;
	unsigned char	*s2_clone;

	s1_len = ft_strlen(s1) - n;
	s2_len = ft_strlen(s2) - n;
	s1_clone = (unsigned char *)s1;
	s2_clone = (unsigned char *)s2;
	while (ft_issamechar(s1_clone[s1_len], s2_clone[s2_len]))
	{
		s1_len++;
		s2_len++;
	}
	return (s1_clone[s1_len] - s2_clone[s2_len]);
}
