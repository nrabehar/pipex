/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_puthex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:05:26 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:31:12 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_pf_get_content(va_list args, t_flags *flag, t_storage *st)
{
	char	*content;

	content = ft_pf_get_hex_content(va_arg(args, unsigned int), flag);
	if (!content)
	{
		if (flag->dot && flag->dot_value < 5)
			st->content = "";
		else
			st->content = "(nil)";
		st->cont_length = 5;
		st->is_null = 1;
	}
	st->content = content;
	st->cont_length = ft_strlen(content);
}

static void	pf_free_hex_content(t_storage *st)
{
	if (st->is_null)
		return ;
	free(st->content);
}

void	ft_pf_puthex(va_list args, t_flags *flag, t_storage *st, char **content)
{
	int	padding_char;

	ft_pf_get_content(args, flag, st);
	if (flag->minus)
		ft_pf_join_hex(st->content, st->format == 'X', content);
	if (flag->dot || flag->zero)
		padding_char = '0';
	else
		padding_char = ' ';
	ft_pfjoin_padding(flag->width - st->cont_length, padding_char, content);
	if (!flag->minus)
		ft_pf_join_hex(st->content, st->format == 'X', content);
	pf_free_hex_content(st);
}
