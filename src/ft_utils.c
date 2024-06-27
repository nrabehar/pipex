/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:05:50 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/20 10:29:25 by nrabehar         ###   ########.fr       */
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

void	ft_get_inpf(t_pipex *dt)
{
	if (dt->is_hd)
		ft_create_hd(dt->av[2]);
	dt->inpf = open(dt->av[1], O_RDONLY, 0644);
	if (dt->inpf < 0)
	{
		dt->errn = errno;
		if (dt->inpf < 0 || close(dt->inpf) < 0)
			ft_printf_fd(STDERR_FILENO, RED "Error%s: %s: %s\n", RESET,
				strerror(dt->errn), dt->av[1]);
	}
}

void	ft_get_outf(t_pipex *dt)
{
	int	derrn;

	if (dt->is_hd)
		dt->outf = open(dt->av[dt->cmds], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		dt->outf = open(dt->av[dt->cmds], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dt->outf < 0)
	{
		derrn = errno;
		if (close(dt->inpf) < 0)
			ft_printf_fd(STDERR_FILENO, RED "Error%s: %s: %s\n", RESET,
				strerror(errno), dt->av[1]);
		dt->errn = derrn;
	}
}

void	ft_closes_std(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
