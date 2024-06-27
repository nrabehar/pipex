/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bct_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:27:47 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/18 15:55:09 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_bct_wcount(char *s)
{
	int	bc[2];
	int	count;

	count = 0;
	bc[0] = 0;
	bc[1] = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			count++;
			while (*s && (!ft_isspace(*s) || (ft_isspace(*s) && bc[0]
						&& !bc[1])))
			{
				if (ft_isopener(*s) && !bc[0])
					bc[0] = *(s++);
				if (ft_iscloser(*s, bc[0]) && bc[0])
					bc[1] = 1;
				s++;
			}
		}
		else
			s++;
	}
	return (count);
}

static int	ft_bct_wlen(char *s)
{
	int	i;
	int	op;
	int	closed;

	op = 0;
	closed = 0;
	while (ft_isspace(*s))
		s++;
	i = 0;
	while (s[i] && (!ft_isspace(s[i]) || (ft_isspace(s[i]) && op && !closed)))
	{
		if (ft_isopener(s[i]) && !op)
			op = s[i++];
		if (ft_iscloser(s[i], op) && op)
			closed = 1;
		i++;
	}
	return (i);
}

static char	*ft_bct_wvalue(char *s, int len)
{
	char	*val;
	char	*tmp;
	int		i;

	tmp = (char *)ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	i = -1;
	while (++i < len)
		tmp[i] = *(s++);
	val = ft_strtrim(tmp, "'");
	free(tmp);
	return (val);
}

char	**ft_bct_split(char *str)
{
	int		count;
	int		wd;
	char	**res;
	int		len;

	count = ft_bct_wcount(str);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res[count] = NULL;
	wd = 0;
	while (wd < count)
	{
		while (ft_isspace(*str))
			str++;
		len = ft_bct_wlen(str);
		res[wd] = ft_bct_wvalue(str, len);
		if (!res[wd])
			return (ft_free_tab((void **)res), NULL);
		str += len;
		wd++;
	}
	return (res);
}
