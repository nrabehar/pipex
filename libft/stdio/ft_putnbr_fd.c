/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:37:09 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:48:10 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
writes the number `n`, to `fd`.
*/

int	ft_putnbr_fd(int n, int fd)
{
	char	*num_str;
	int		length;

	num_str = ft_itoa(n);
	if (num_str)
		return (-1);
	length = ft_putstr_fd(num_str, fd);
	return (free(num_str), length);
}
