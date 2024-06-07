/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:06:29 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/08 22:50:33 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char	*ft_pf_pass_flag(char *fmt)
{
	while (ft_pf_is_in_flags(*fmt))
		fmt++;
	if (ft_pf_is_format(*fmt) && (*fmt == 'z' && *(fmt + 1) == 'u'))
		fmt++;
	fmt++;
	return (fmt);
}

static char	*pf_consume_no_format(char *fmt, char **content)
{
	char	*next_percent;
	char	*tmp_fmt;

	next_percent = ft_strchr(fmt, '%');
	if (!next_percent)
	{
		ft_pf_join_content(content, fmt);
		return (NULL);
	}
	tmp_fmt = ft_substr(fmt, 0, next_percent - fmt);
	if (!tmp_fmt)
	{
		free(*content);
		*content = NULL;
		return (NULL);
	}
	ft_pf_join_content(content, tmp_fmt);
	free(tmp_fmt);
	return (next_percent);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	char	*content;
	int		length;

	if (!fmt || !*fmt)
		return (0);
	va_start(args, fmt);
	length = 0;
	content = NULL;
	while (fmt && *fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_pf_parse_value(args, fmt, &content);
			fmt = ft_pf_pass_flag((char *)fmt);
		}
		else
			fmt = pf_consume_no_format((char *)fmt, &content);
	}
	va_end(args);
	length = ft_putstr_fd(content, 1);
	free(content);
	return (length);
}

int	ft_printf_fd(int fd, const char *fmt, ...)
{
	va_list	args;
	char	*content;
	int		length;

	if (fd < 0 || !fmt || !*fmt)
		return (0);
	va_start(args, fmt);
	length = 0;
	content = NULL;
	while (fmt && *fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_pf_parse_value(args, fmt, &content);
			fmt = ft_pf_pass_flag((char *)fmt);
		}
		else
			fmt = pf_consume_no_format((char *)fmt, &content);
	}
	va_end(args);
	length = ft_putstr_fd(content, fd);
	free(content);
	return (length);
}
