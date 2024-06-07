/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:35:55 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:48:55 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int		length;
	char	*str;

	str = ft_strjoin(s, "\n");
	if (!str)
		return (-1);
	length = ft_putstr_fd(str, fd);
	return (free(str), length);
}
