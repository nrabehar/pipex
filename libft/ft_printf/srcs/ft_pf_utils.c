/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:07:20 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 20:40:40 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>

/*
		switch a lower character string to upper
		eg :
		- inp = "aBcDeF0"
		- out = "AbCdEf0"
*/

char	*ft_pfswitch_case(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

void	ft_pfjoin_padding(int size, const int c, char **content)
{
	char	*padding;
	int		i;

	if (size <= 0)
		return ;
	padding = (char *)ft_calloc(size + 1, sizeof(char));
	if (!padding)
		return ;
	i = 0;
	while (i < size)
	{
		padding[i] = c;
		i++;
	}
	ft_pf_join_content(content, padding);
	free(padding);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated;
	size_t	max_size;

	max_size = (size_t)-1;
	if (size && (nmemb > max_size / size))
		return (NULL);
	allocated = malloc(nmemb * size);
	if (!allocated)
		return (NULL);
	max_size = 0;
	while (max_size < nmemb * size)
		((unsigned char *)allocated)[max_size++] = 0;
	return (allocated);
}

void	ft_pf_join_content(char **content, char *to_join)
{
	char	*res;

	if (!*content)
	{
		*content = ft_strdup(to_join);
		return ;
	}
	res = ft_strjoin(*content, to_join);
	free(*content);
	if (!res)
		*content = NULL;
	else
		*content = res;
}

size_t	ft_pfget_flags_size(char const *str)
{
	size_t	size;

	size = 0;
	while ((str[size] && ft_pf_is_in_flags(str[size])) || (size > 0
			&& ft_pf_is_in_flags(str[size - 1]) && ft_pf_is_format(str[size])))
		++size;
	if (ft_pf_is_format(str[size]))
		++size;
	return (size);
}
