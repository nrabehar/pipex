/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isopener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:34:19 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/18 16:19:51 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isopener(char c)
{
	char	*openers;

	openers = "'\"({<";
	while (*openers && *openers != c)
		openers++;
	return (*openers == c);
}
