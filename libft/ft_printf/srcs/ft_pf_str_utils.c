/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:12:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/04/18 13:47:11 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_pf_strlen(char const *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_pf_substr(char const *str, size_t start, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)ft_pf_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[start + i] && i < len)
	{
		res[i] = str[start + i];
		i++;
	}
	return (res);
}

char	*ft_pf_strdup(char const *str)
{
	char	*res;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_pf_strlen(str);
	res = ft_pf_substr(str, 0, len);
	return (res);
}

int	ft_pf_putstr(char const *str)
{
	int	size;

	size = ft_pf_strlen(str);
	if (!str || size == 0)
		return (0);
	write(1, str, size);
	return (size);
}

int	ft_pf_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
