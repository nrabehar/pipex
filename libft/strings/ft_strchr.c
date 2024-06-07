/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:58:04 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:56:35 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
returns a pointer to the first occurrence of the character c in the string s.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_clone;

	s_clone = (char *)s;
	i = 0;
	while (s_clone[i] && s_clone[i] != (unsigned char)c)
		i++;
	if (s_clone && s_clone[i] == (unsigned char)c)
		return (&s_clone[i]);
	return (NULL);
}
