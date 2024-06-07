/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_flags_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 10:12:49 by nrabehar          #+#    #+#             */
/*   Updated: 2024/04/18 13:46:44 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
		check if the given character is a format
*/

int	ft_pf_is_format(int c)
{
	char	*params;

	params = "cspdiuxX%z";
	while (*params)
	{
		if (*params == (char)c)
			return (1);
		params++;
	}
	return (0);
}

/*
		check if the given character is a flag
*/

int	ft_pf_is_flag(int c)
{
	char	*flags;

	flags = "0# +-.";
	while (*flags)
	{
		if (*flags == (char)c)
			return (1);
		flags++;
	}
	return (0);
}

/*
		check if the given charcter is a number flag
		1-9 because 0 is a flag
*/

int	ft_pf_is_num_flag(int c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}

/*
		check if the given character is a valid flag
*/

int	ft_pf_is_in_flags(int c)
{
	if (ft_pf_is_flag(c) || ft_pf_is_num_flag(c))
		return (1);
	return (0);
}

int	ft_pf_parse_format_flag(char const *str, t_storage *st, int start)
{
	if (str[start] == 'z' && str[start + 1] != 'u')
	{
		st->format = '\0';
		return (0);
	}
	st->format = str[start];
	return (1);
}
