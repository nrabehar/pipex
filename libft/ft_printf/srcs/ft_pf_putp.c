/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:26:43 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:36:25 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	pf_get_content(unsigned long int n, t_storage *st)
{
	char	*content;

	if (n == 0)
	{
		st->content = ft_strdup("(nil)");
		if (!st->content)
			return (0);
		st->cont_length = ft_strlen(st->content);
		return (1);
	}
	content = ft_pf_hextoa(n);
	if (!content)
		return (0);
	st->content = content;
	st->cont_length = ft_strlen(st->content) + 2;
	return (1);
}

static void	ft_pf_print_ptr(unsigned long int n, t_storage *st, char **content)
{
	if (n > 0)
		ft_pf_join_content(content, "0x");
	ft_pf_join_content(content, st->content);
	free(st->content);
}

void	ft_pf_putptr(va_list args, t_flags *flag, t_storage *st, char **content)
{
	unsigned long int	num;

	num = va_arg(args, unsigned long int);
	if (!pf_get_content(num, st))
		return ;
	if (flag->minus)
		ft_pf_print_ptr(num, st, content);
	if (flag->dot || flag->zero)
		ft_pfjoin_padding(flag->width - st->cont_length, '0', content);
	else
		ft_pfjoin_padding(flag->width - st->cont_length, ' ', content);
	if (!flag->minus)
		ft_pf_print_ptr(num, st, content);
}
