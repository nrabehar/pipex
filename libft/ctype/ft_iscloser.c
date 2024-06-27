/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscloser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:33:47 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/18 16:20:14 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_iscloser(int c, int op)
{
	if (op == '{')
		return ('}' == c);
	if (op == '\'')
		return (op == c);
	if (op == '"')
		return (op == c);
	if (op == '(')
		return (')' == c);
	if (op == '<')
		return ('>' == c);
	return (-1);
}
