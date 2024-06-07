/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:22:14 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_charchr(char const *str, char const c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_charchr(set, s1[i]))
		i++;
	return (i);
}

static size_t	get_len(char const *s1, char const *set, size_t start)
{
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s1);
	i = s_len - 1;
	while (i >= start && ft_charchr(set, s1[i]))
		i--;
	if (i > start)
		return ((i - start) + 1);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = get_start(s1, set);
	len = get_len(s1, set, start);
	trimmed = ft_substr(s1, start, len);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
