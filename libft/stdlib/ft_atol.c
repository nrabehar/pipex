/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:00:12 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	ft_atol(const char *nptr)
{
	int		neg;
	long	res;
	size_t	i;

	i = 0;
	neg = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			neg = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res * neg);
}
