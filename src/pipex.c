/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:59:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/06 11:18:36 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pusage(void)
{
	ft_printf_fd(STDERR_FILENO, BLUE "USAGE%s: %s\n", RESET,
		"./pipex <infile> cmd1 cmd2 <outfile>");
}

static void	ft_get_inpf(t_pipex *dt)
{
	dt->inpf = open(dt->av[1], O_RDONLY, 0644);
	if (dt->inpf < 0)
		dt->errn = errno;
}

static void	ft_get_outf(t_pipex *dt)
{
	int	derrn;

	dt->outf = open(dt->av[dt->cmds], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dt->outf < 0)
	{
		derrn = errno;
		if (dt->inpf < 0 || close(dt->inpf) < 0)
			ft_printf_fd(STDERR_FILENO, RED "Error%s: %s: %s\n", RESET,
				strerror(dt->errn), dt->av[1]);
		dt->errn = derrn;
	}
}

static void	ft_get_mfds(char **av, char **ep, t_pipex *dt)
{
	dt->errn = 0;
	dt->av = av;
	dt->ep = ep;
	ft_get_inpf(dt);
	ft_get_outf(dt);
}

int	main(int ac, char const *av[], char const *ep[])
{
	int		status;
	pid_t	pid;
	t_pipex	dt;

	if (ac != 5)
	{
		ft_pusage();
		ft_throw(RED "Error" RESET, "invalid argument", 0);
	}
	dt.cmds = ac - 1;
	dt.cmd_id = 2;
	ft_get_mfds((char **)av, (char **)ep, &dt);
	ft_get_pths(&dt);
	pid = fork();
	if (pid < 0)
		ft_throw(RED "Fork" RESET, strerror(errno), NULL);
	if (pid == 0)
		ft_pipex(&dt);
	else
		waitpid(pid, &status, 0);
	ft_free_pths(dt.pths);
	close(dt.inpf);
	close(dt.outf);
	return (WEXITSTATUS(status));
}
