/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:55:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:35:48 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	pf_manage_flag(t_flags *flag, t_storage *st)
{
	if (st->cont_length == 0)
		st->cont_length += ft_strlen(st->content);
	if (flag->dot_value >= st->cont_length)
		flag->dot_value -= st->cont_length;
	else
		flag->dot_value = 0;
	if (flag->dot_value > 0)
		st->cont_length += flag->dot_value;
	flag->width -= st->cont_length;
}

static void	ft_pfjoin_sign(int is_neg, t_flags *flag, char **content)
{
	if (is_neg && !flag->dot_value && flag->zero && !flag->dot)
		ft_pf_join_content(content, "-");
	else if (flag->plus && !is_neg)
	{
		ft_pf_join_content(content, "+");
		flag->plus = 0;
		flag->width--;
	}
	else if (flag->space && !is_neg)
	{
		ft_pf_join_content(content, " ");
		flag->space = 0;
		flag->width--;
	}
}

static void	ft_pfjoin_nbr(int is_neg, t_flags *flag, t_storage *st,
		char **content)
{
	if (is_neg && ((flag->dot_value || !flag->zero) || (flag->dot
				&& flag->zero)))
		ft_pf_join_content(content, "-");
	else if (!flag->zero)
		ft_pfjoin_sign(is_neg, flag, content);
	if (flag->dot_value > 0)
		ft_pfjoin_padding(flag->dot_value, '0', content);
	ft_pf_join_content(content, st->content);
	flag->dot = 0;
}

static void	ft_pf_print_n(long num, t_flags *flag, t_storage *st,
		char **content)
{
	int	is_neg;

	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		num *= -1;
		flag->width--;
	}
	st->content = ft_pf_ltoa(num);
	if (!st->content)
		return ;
	ft_pfjoin_sign(is_neg, flag, content);
	pf_manage_flag(flag, st);
	if (flag->minus)
		ft_pfjoin_nbr(is_neg, flag, st, content);
	if ((flag->dot && flag->zero) || (!flag->dot && !flag->zero))
		ft_pfjoin_padding(flag->width, ' ', content);
	else
		ft_pfjoin_padding(flag->width, '0', content);
	if (!flag->minus)
		ft_pfjoin_nbr(is_neg, flag, st, content);
	free(st->content);
}

void	ft_pf_putn(va_list args, t_flags *flag, t_storage *st, char **content)
{
	int	num;

	num = va_arg(args, int);
	if (num == 0 && !flag->dot_value && flag->dot)
	{
		ft_pfjoin_padding(flag->width, ' ', content);
		return ;
	}
	ft_pf_print_n(num, flag, st, content);
}
