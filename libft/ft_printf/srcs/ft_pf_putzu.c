/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putzu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:13:17 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:39:37 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	pf_manage_flag(t_flags *flag, t_storage *st)
{
	if (flag->dot_value >= st->cont_length)
		flag->dot_value -= st->cont_length;
	else
		flag->dot_value = 0;
	if (flag->dot_value > 0)
		st->cont_length += flag->dot_value;
	flag->width -= st->cont_length;
}

static void	ft_pfjoin_sign(t_flags *flag, char **content)
{
	if (flag->plus)
	{
		ft_pf_join_content(content, "+");
		flag->plus = 0;
		flag->width--;
	}
	else if (flag->space)
	{
		ft_pf_join_content(content, " ");
		flag->space = 0;
		flag->width--;
	}
}

static void	ft_pf_putzu_base(t_flags *flag, t_storage *st, char **content)
{
	if (!flag->zero)
		ft_pfjoin_sign(flag, content);
	if (flag->dot_value > 0)
		ft_pfjoin_padding(flag->dot_value, '0', content);
	ft_pf_join_content(content, st->content);
	flag->dot = 0;
}

static void	ft_pf_print_zu(unsigned long num, t_flags *flag, t_storage *st,
		char **content)
{
	st->content = ft_pf_utoa(num);
	if (!st->content)
		return ;
	st->cont_length += ft_strlen(st->content);
	ft_pfjoin_sign(flag, content);
	pf_manage_flag(flag, st);
	if (flag->minus)
		ft_pf_putzu_base(flag, st, content);
	if ((flag->dot && flag->zero) || (!flag->dot && !flag->zero))
		ft_pfjoin_padding(flag->width, ' ', content);
	else
		ft_pfjoin_padding(flag->width, '0', content);
	if (!flag->minus)
		ft_pf_putzu_base(flag, st, content);
	free(st->content);
}

void	ft_pf_putzu(va_list args, t_flags *flag, t_storage *st, char **content)
{
	unsigned long	num;

	num = va_arg(args, unsigned long);
	if (num == 0 && !flag->dot_value && flag->dot)
	{
		ft_pfjoin_padding(flag->width, ' ', content);
		return ;
	}
	ft_pf_print_zu(num, flag, st, content);
}
