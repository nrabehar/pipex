/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:08:44 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:17:41 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

char	*ft_pf_get_flags(char const *str)
{
	size_t	i;
	size_t	size;
	char	*flags;

	size = ft_pfget_flags_size(str);
	flags = (char *)ft_calloc(size + 1, sizeof(char));
	if (!flags)
		return (NULL);
	i = 0;
	while (str[i] && ft_pf_is_in_flags(str[i]))
	{
		flags[i] = str[i];
		i++;
	}
	while (i < size && str[i] && ft_pf_is_format(str[i]))
	{
		flags[i] = str[i];
		i++;
	}
	flags[i] = '\0';
	return (flags);
}

static int	ft_parse_precision(char const *str, t_flags *flag)
{
	size_t	i;

	i = 1;
	while (str[i] && ft_isdigit(str[i]))
	{
		flag->dot_value *= 10;
		flag->dot_value += str[i] - 48;
		i++;
	}
	flag->dot = 1;
	return (i - 1);
}

static int	ft_parse_width(char const *str, t_flags *flag)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		flag->width *= 10;
		flag->width += str[i] - 48;
		i++;
	}
	return (i - 1);
}

static void	ft_parse_left(t_flags *flag)
{
	flag->minus = 1;
	flag->zero = 0;
}

void	ft_parse_flags(t_flags *flag, t_storage *st, int i)
{
	while (ft_pf_is_in_flags(st->flags[i]) || ft_pf_is_format(st->flags[i]))
	{
		if (st->flags[i] == '-')
			ft_parse_left(flag);
		if (st->flags[i] == '+')
			flag->plus = 1;
		if (st->flags[i] == '#')
			flag->hash = 1;
		if (st->flags[i] == ' ')
			flag->space = 1;
		if (st->flags[i] == '0')
			flag->zero = 1;
		if (st->flags[i] == '.')
			i += ft_parse_precision(&st->flags[i], flag) + 1;
		if (ft_isdigit(st->flags[i]))
			i += ft_parse_width(&st->flags[i], flag);
		if (ft_pf_is_format(st->flags[i]))
		{
			ft_pf_parse_format_flag(st->flags, st, i);
			break ;
		}
		i++;
	}
}
