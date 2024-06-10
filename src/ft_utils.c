/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:50 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/10 09:16:44 by nrabehar         ###   ########.fr       */
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
/**
 * @brief Retrieves the PATH environment variable and splits it into paths.
 * @param dt A pointer to the t_pipex structure.
 */
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

/**
 * @brief Gets the full path of a command.
 * @param cmd The command name.
 * @param pths An array of paths.
 * @return The full path of the command, or NULL if not found.
 */
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

/**
 * @brief Creates a here_doc file and writes input until a delimiter is reached.
 * @param delimiter The delimiter string.
 */
void	ft_create_hd(char const *delimiter)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_throw("Here_doc", strerror(errno), "here_doc");
	while (1)
	{
		ft_printf_fd(STDOUT_FILENO, "pipex heredoc> ");
		line = ft_gnl(STDIN_FILENO);
		if (!line || (line && ft_strncmp(line, delimiter,
					ft_strlen(delimiter)) == 0))
			break ;
		ft_printf_fd(fd, line);
		free(line);
	}
	free(line);
	if (close(fd) < 0)
		ft_throw("Here_doc", strerror(errno), "here_doc");
}
