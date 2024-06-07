/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:34:16 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:48:03 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
writes the string `s`, to `fd`.
*/

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}
