/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:38:52 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/20 15:51:24 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_pths(t_pipex *dt)
{
	char	**epc;

	epc = dt->ep;
	while (*epc && !ft_strnstr(*epc, "PATH=", 5))
		epc++;
	if (!*epc)
		ft_throw("Path", "Failed to get evironement path", NULL);
	dt->pths = ft_split(*epc + 5, ':');
	if (!dt->pths)
		ft_throw("Path", "Failed to get evironement path", NULL);
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

int	ft_isexist_cmd(char *cmd, char **pths)
{
	char	**cmdarg;
	char	*cmdpt;

	cmdarg = ft_bct_split(cmd);
	if (!cmdarg)
		return (0);
	cmdpt = ft_get_cmd_pth(cmdarg[0], pths);
	ft_free_pths(cmdarg);
	if (!cmdpt)
		return (0);
	free(cmdpt);
	return (1);
}

void	ft_create_hd(char const *lim)
{
	int		fd;
	char	*line;
	char	*joined;
	size_t	len;

	fd = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_throw("Here_doc", strerror(errno), "here_doc");
	joined = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "heredoc>> ", 10);
		line = ft_gnl(STDIN_FILENO);
		if (!line || (line && ft_strncmp(line, lim, ft_strlen(lim)) == 0))
			break ;
		ft_pf_join_content(&joined, line);
		free(line);
	}
	len = ft_strlen(joined);
	if (!line && joined[len - 2] == '\n')
		len--;
	write(fd, joined, len);
	close(fd);
	return (free(line), free(joined));
}
