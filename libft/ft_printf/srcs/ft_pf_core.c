/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:14:11 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:21:43 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_fetch_value(va_list args, t_flags *flag, t_storage *st,
		char **content)
{
	if (st->format == 'c' || st->format == '%')
		ft_pf_putc(args, flag, st, content);
	if (st->format == 's')
		ft_pf_puts(args, flag, st, content);
	if (st->format == 'x' || st->format == 'X')
		ft_pf_puthex(args, flag, st, content);
	if (st->format == 'p')
		ft_pf_putptr(args, flag, st, content);
	if (st->format == 'd' || st->format == 'i')
		ft_pf_putn(args, flag, st, content);
	if (st->format == 'u')
		ft_pf_putu(args, flag, st, content);
	if (st->format == 'z')
		ft_pf_putzu(args, flag, st, content);
}

static t_flags	ft_pf_init_flags(void)
{
	t_flags	flag;

	flag.minus = 0;
	flag.plus = 0;
	flag.hash = 0;
	flag.dot = 0;
	flag.dot_value = 0;
	flag.width = 0;
	flag.zero = 0;
	flag.space = 0;
	return (flag);
}

static t_storage	*ft_pf_init_storage(const char *fmt)
{
	t_storage	*st;

	st = (t_storage *)ft_calloc(1, sizeof(t_storage));
	if (!st)
		return (NULL);
	st->flags = ft_pf_get_flags(fmt);
	if (!st->flags)
		return (free(st), NULL);
	st->cont_length = 0;
	st->is_null = 0;
	st->content = NULL;
	return (st);
}

void	ft_pf_parse_value(va_list args, char const *fmt, char **content)
{
	t_flags		flag;
	t_storage	*st;

	flag = ft_pf_init_flags();
	st = ft_pf_init_storage(fmt);
	if (!st)
		return ;
	ft_parse_flags(&flag, st, 0);
	ft_fetch_value(args, &flag, st, content);
	return (free(st->flags), free(st));
}
