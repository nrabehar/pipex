/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:30:04 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/14 15:59:26 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi_base(char const *str, char *base)
{
	int	value;
	int	id;
	int	str_id;
	int	base_length;

	base_length = (int)ft_strlen(base);
	value = 0;
	str_id = 0;
	while (str && str[str_id] && !ft_isspace(str[str_id]))
	{
		id = 0;
		while (ft_tolower(base[id]) != ft_tolower(str[str_id]))
			id++;
		if (id < base_length)
		{
			value *= base_length;
			value += id;
		}
		str_id++;
	}
	return (value);
}
