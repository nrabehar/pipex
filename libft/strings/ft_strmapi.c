/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:32:31 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*s_clone;
	char	*res;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	s_clone = (char *)s;
	res = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s_clone[i])
	{
		res[i] = f(i, s_clone[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
