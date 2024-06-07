/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:08:56 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:32:07 by nrabehar         ###   ########.fr       */
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

static int	ft_pfjoin_sign(t_flags *flag, char **content)
{
	int	i;

	i = 0;
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
	return (i);
}

static int	ft_pf_putu_base(t_flags *flag, t_storage *st, char **content)
{
	int	length;

	length = 0;
	if (!flag->zero)
		length += ft_pfjoin_sign(flag, content);
	if (flag->dot_value > 0)
		ft_pfjoin_padding(flag->dot_value, '0', content);
	ft_pf_join_content(content, st->content);
	flag->dot = 0;
	return (length);
}

static int	ft_pf_print_u(unsigned int num, t_flags *flag, t_storage *st, char **content)
{
	int	length;

	st->content = ft_pf_utoa(num);
	if (!st->content)
		return (0);
	st->cont_length += ft_strlen(st->content);
	length = ft_pfjoin_sign(flag, content);
	pf_manage_flag(flag, st);
	if (flag->minus)
		length += ft_pf_putu_base(flag, st, content);
	if ((flag->dot && flag->zero) || (!flag->dot && !flag->zero))
		ft_pfjoin_padding(flag->width, ' ', content);
	else
		ft_pfjoin_padding(flag->width, '0', content);
	if (!flag->minus)
		length += ft_pf_putu_base(flag, st, content);
	free(st->content);
	return (length);
}

void	ft_pf_putu(va_list args, t_flags *flag, t_storage *st, char **content)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (num == 0 && !flag->dot_value && flag->dot)
	{
		ft_pfjoin_padding(flag->width, ' ', content);
		return ;
	}
	ft_pf_print_u(num, flag, st, content);
}
