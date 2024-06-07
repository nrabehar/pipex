/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:19:24 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 22:19:52 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_get_len(long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_ltoa(long n)
{
	long	num;
	char	*res;
	size_t	len;

	num = n;
	if (n < 0)
		num *= -1;
	len = ft_get_len(n);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (len--)
	{
		res[len] = (num % 10) + 48;
		num /= 10;
	}
	if (n < 0)
		res[0] = 45;
	return (res);
}
