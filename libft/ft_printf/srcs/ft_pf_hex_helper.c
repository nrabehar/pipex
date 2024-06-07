/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_hex_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:01:18 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:27:38 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_pf_join_hex(const char *hex_content, int is_upper, char **content)
{
	if (is_upper)
		ft_pfswitch_case((char *)hex_content);
	ft_pf_join_content(content, (char *)hex_content);
}

static void	ft_pf_fill_dot_content(char *content, int *size, t_flags *flag)
{
	int	i;
	int	j;

	i = flag->dot_value;
	j = *size;
	while (i > 0)
	{
		content[j] = '0';
		j--;
		i--;
	}
	*size = j;
	flag->dot_value = 0;
}

static void	pf_fill_content(char *content, unsigned int n, int size,
		t_flags *flag)
{
	char	*base;

	base = "0123456789abcdef";
	content[size--] = '\0';
	if (n == 0 && size >= 0)
	{
		content[size--] = '0';
		ft_pf_fill_dot_content(content, &size, flag);
		return ;
	}
	while (n)
	{
		content[size] = base[n % 16];
		n /= 16;
		size--;
	}
	ft_pf_fill_dot_content(content, &size, flag);
	if (flag->hash)
	{
		content[size--] = 'x';
		content[size--] = '0';
	}
}

static void	ft_pf_adjust_hex_flag(unsigned int num, t_flags *flag, int *size)
{
	flag->dot_value -= *size;
	if (flag->hash && num != 0)
		flag->dot_value += 2;
	if (flag->zero && !flag->dot)
		flag->dot_value = flag->width - *size;
	if (flag->dot_value > 0)
		*size += flag->dot_value;
	if (flag->dot)
		flag->zero = 0;
	flag->dot = 0;
}

char	*ft_pf_get_hex_content(unsigned int n, t_flags *flag)
{
	int		size;
	char	*content;

	size = ft_pf_get_num_len(n, 16);
	if (n == 0 && flag->dot && flag->dot_value == 0)
	{
		content = (char *)ft_calloc(1, sizeof(char));
		if (!content)
			return (NULL);
		if (flag->dot)
			flag->zero = 0;
		flag->dot = 0;
		return (content);
	}
	if (flag->hash && n != 0)
		size += 2;
	ft_pf_adjust_hex_flag(n, flag, &size);
	content = (char *)ft_calloc(size +1 ,sizeof(char));
	if (!content)
		return (NULL);
	pf_fill_content(content, n, size, flag);
	ft_pf_adjust_hex_flag(n, flag, &size);
	return (content);
}
