/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:23:41 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/03 23:31:36 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_gnl_join(char *s1, char *s2)
{
	size_t	size;
	char	*res;
	size_t	i;
	size_t	res_id;

	size = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (free(s1), NULL);
	res_id = 0;
	while (s1 && s1[res_id])
	{
		res[res_id] = s1[res_id];
		res_id++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		res[res_id + i] = s2[i];
		i++;
	}
	if (!res[0])
		return (free(res), free(s1), NULL);
	return (free(s1), res);
}

static char	*ft_gnl_update_st(char *st_buf, char *line)
{
	char	*next;
	char	*new;

	if (!st_buf)
		return (NULL);
	if (!line || !*st_buf)
		return (free(st_buf), NULL);
	next = ft_strchr(st_buf, 10);
	if (!next)
		return (free(st_buf), NULL);
	if (!*(next + 1))
		return (free(st_buf), NULL);
	new = ft_strdup(next + 1);
	if (!new)
		return (free(st_buf), NULL);
	return (free(st_buf), new);
}

static char	*gnl_find(char **st_buf)
{
	char	*line;
	size_t	i;

	if (!*st_buf || !**st_buf)
		return (NULL);
	i = 0;
	while ((*st_buf)[i])
		if ((*st_buf)[i++] == 10)
			break ;
	line = (char *)ft_calloc(sizeof(char), i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while ((*st_buf)[i])
	{
		line[i] = (*st_buf)[i];
		if (line[i] == 10)
			break ;
		i++;
	}
	return (line);
}

static char	*gnl_read(int fd, char **st_buf)
{
	int		buf_read;
	char	*buf;
	char	*line;

	buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf_read = 1;
	while (buf_read)
	{
		buf_read = read(fd, buf, BUFFER_SIZE);
		if (buf_read < 0)
			return (free(buf), NULL);
		buf[buf_read] = '\0';
		*st_buf = ft_gnl_join(*st_buf, buf);
		if (!*st_buf)
			return (free(buf), NULL);
		if (ft_strchr(buf, '\n'))
			buf_read = 0;
	}
	line = gnl_find(st_buf);
	if (!line)
		return (free(buf), NULL);
	return (free(buf), line);
}

char	*ft_gnl(int fd)
{
	char		*line;
	static char	*st_buf[FD_MAX];

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = gnl_read(fd, &st_buf[fd]);
	st_buf[fd] = ft_gnl_update_st(st_buf[fd], line);
	return (line);
}
