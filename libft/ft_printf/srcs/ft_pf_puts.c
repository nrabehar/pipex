/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_puts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:33:42 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:37:17 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	pf_get_dot_content(char const *content, t_flags *flag,
		t_storage *st)
{
	st->content = ft_substr(content, 0, flag->dot_value);
	if (!st->content)
		return (0);
	st->cont_length = ft_strlen(st->content);
	return (1);
}

static int	pf_get_null_content(t_flags *flag, t_storage *st)
{
	if (flag->dot && flag->dot_value < 6)
		st->content = ft_strdup("");
	else
		st->content = ft_strdup("(null)");
	if (!st->content)
		return (0);
	st->cont_length = 6;
	return (1);
}

static int	pf_get_content(va_list args, t_flags *flag, t_storage *st)
{
	char	*content;
	int		ret;

	ret = 1;
	content = va_arg(args, char *);
	if (!content)
		ret = pf_get_null_content(flag, st);
	else if (flag->dot && flag->dot_value < (int)ft_strlen(content))
		ret = pf_get_dot_content(content, flag, st);
	else
	{
		st->content = ft_strdup(content);
		st->cont_length = ft_strlen(content);
	}
	flag->dot = 0;
	return (ret);
}

void	ft_pf_puts(va_list args, t_flags *flag, t_storage *st, char **content)
{
	if (!pf_get_content(args, flag, st))
		return ;
	if (flag->minus)
		ft_pf_join_content(content, st->content);
	ft_pfjoin_padding(flag->width - st->cont_length, ' ', content);
	if (!flag->minus)
		ft_pf_join_content(content, st->content);
	free(st->content);
}
