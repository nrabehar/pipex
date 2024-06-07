/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:09:40 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_concat(char *res, char const *s1, char const *s2)
{
	size_t	i;
	size_t	res_id;

	i = 0;
	res_id = 0;
	while (s1[i])
	{
		res[res_id] = s1[i];
		i++;
		res_id++;
	}
	i = 0;
	while (s2[i])
	{
		res[res_id] = s2[i];
		i++;
		res_id++;
	}
	res[res_id] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	size;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	size = s1_len + s2_len;
	res = (char *)ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_concat(res, s1, s2);
	return (res);
}
