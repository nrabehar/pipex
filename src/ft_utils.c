/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:50 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/06 09:08:21 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_throw(char const *title, char *m, char const *pt)
{
	ft_printf_fd(STDERR_FILENO, RED "%s%s: ", title, RESET);
	if (m && !pt)
		ft_printf_fd(STDERR_FILENO, "%s\n", m);
	else if (m && pt)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", m, pt);
	exit(EXIT_FAILURE);
}

void	ft_free_pths(char **pths)
{
	size_t	i;

	i = 0;
	while (pths[i])
	{
		free(pths[i]);
		i++;
	}
	free(pths);
}

void	ft_get_pths(t_pipex *dt)
{
	char	**epc;

	epc = dt->ep;
	while (*epc && !ft_strnstr(*epc, "PATH=", 5))
		epc++;
	if (!*epc)
	{
		close(dt->inpf);
		close(dt->inpf);
		ft_throw("Path", "Failed to get evironement path", NULL);
	}
	dt->pths = ft_split(*epc + 5, ':');
	if (!dt->pths)
	{
		close(dt->inpf);
		close(dt->inpf);
		ft_throw("Path", "Failed to get evironement path", NULL);
	}
}

char	*ft_get_cmd_pth(char *cmd, char **pths)
{
	char	*tmp;
	int		i;
	char	*pth;

	if (!cmd)
		return (NULL);
	i = -1;
	while (pths[++i])
	{
		tmp = ft_strjoin(pths[i], "/");
		if (!tmp)
			return (NULL);
		pth = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!pth)
			return (NULL);
		if (access(pth, F_OK | X_OK) == 0)
			return (pth);
		free(pth);
	}
	return (NULL);
}

void	ft_create_hd(char const *delimiter)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_throw("Here_doc", strerror(errno), "here_doc");
	while (1)
	{
		write(STDOUT_FILENO, "heredoc>> ", 10);
		line = ft_gnl(STDIN_FILENO);
		if (!line || (line && ft_strncmp(line, delimiter,
					ft_strlen(delimiter)) == 0))
			break ;
		if (write(fd, line, ft_strlen(line)) < 0)
			return (free(line), close(fd), ft_throw("Here_doc",
					"Failed to write", "here_doc"));
		free(line);
	}
	free(line);
	if (close(fd) < 0)
		ft_throw("Here_doc", strerror(errno), "here_doc");
}
