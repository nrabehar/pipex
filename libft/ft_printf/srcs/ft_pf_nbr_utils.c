/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_nbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 09:19:09 by nrabehar          #+#    #+#             */
/*   Updated: 2024/04/18 13:46:51 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
	get the length of the number
*/

size_t	ft_pf_get_num_len(unsigned long int num, int base_length)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= base_length;
		len++;
	}
	return (len);
}

static size_t	ft_pf_get_int_len(long num, int base_length)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		len++;
	while (num)
	{
		num /= base_length;
		len++;
	}
	return (len);
}

/*
	Get string version of the (int) number
*/

char	*ft_pf_ltoa(long num)
{
	char	*result;
	size_t	size;
	int		is_neg;

	size = 0;
	is_neg = 0;
	size += ft_pf_get_int_len(num, 10);
	if (num < 0)
	{
		is_neg = 1;
		num *= -1;
	}
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while ((int)size > is_neg - 1)
	{
		result[size] = (num % 10) + 48;
		num /= 10;
		size--;
	}
	if (is_neg)
		result[size] = '-';
	return (result);
}

/*
	Get string version of the (unsigned long) number
*/

char	*ft_pf_utoa(unsigned long num)
{
	size_t	size;
	char	*result;

	size = ft_pf_get_num_len(num, 10);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while (size)
	{
		result[size] = (num % 10) + 48;
		num /= 10;
		size--;
	}
	result[0] = (num % 10) + 48;
	return (result);
}

/*
	Get string version of the (unsigned long int) number
	for hexadecimal.
*/

char	*ft_pf_hextoa(unsigned long int num)
{
	size_t	size;
	char	*result;

	size = ft_pf_get_num_len(num, 16);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while (num)
	{
		if (num % 16 < 10)
			result[size] = (num % 16) + 48;
		else
			result[size] = ((num % 16) - 10) + 97;
		num /= 16;
		size--;
	}
	return (result);
}
