/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:46:13 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_same(char const c1, char const c2)
{
	if (!c1 || !c2)
		return (0);
	if (c1 == c2)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	char	*big_clone;

	little_len = ft_strlen(little);
	big_clone = (char *)big;
	if (!little_len)
		return (big_clone);
	if (len == 0)
		return (NULL);
	i = 0;
	while (big_clone[i])
	{
		j = 0;
		while (i + j < len && is_same(big_clone[i + j], little[j]))
			j++;
		if (j == little_len)
			return (&big_clone[i]);
		i++;
	}
	return (NULL);
}
