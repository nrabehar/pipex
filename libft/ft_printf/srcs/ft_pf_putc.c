/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:19:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:49:48 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_pf_putc(va_list args, t_flags *flag, t_storage *st, char **content)
{
	char		c;

	if (st->format == '%')
		c = st->format;
	else
		c = va_arg(args, int);
	if (flag->minus)
		ft_pf_join_content(content, &c);
	ft_pfjoin_padding(flag->width - 1, ' ', content);
	if (!flag->minus)
		ft_pf_join_content(content, &c);
}
