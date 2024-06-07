/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:59:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/05 15:49:38 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pusage(void)
{
	ft_printf_fd(STDERR_FILENO, BLUE "USAGE%s: %s\n", RESET,
		"<infile> cmd1 cmd2 <outfile>");
}

static int	ft_get_inpf(char const *pth, t_pipex *dt)
{
	int	inpf_fd;

	inpf_fd = open(pth, O_RDONLY, 0644);
	if (inpf_fd < 0)
		dt->errn = errno;
	return (inpf_fd);
}

static int	ft_get_outf(char const *pth, int inpf)
{
	int	outf;

	outf = open(pth, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outf < 0)
	{
		if (close(inpf) < 0)
			ft_printf_fd(STDERR_FILENO,
				BLUE "Warning%s : Failed to close input file\n", RESET);
		ft_throw(pth, NULL, 1, NULL);
	}
	return (outf);
}

static void	ft_get_mfds(char **av, char **ep, t_pipex *dt)
{
	dt->errn = 0;
	dt->av = av;
	dt->ep = ep;
	dt->inpf = ft_get_inpf(dt->av[1], dt);
	dt->outf = ft_get_outf(dt->av[dt->cmds], dt->inpf);
}

int	main(int ac, char const *av[], char const *ep[])
{
	int		status;
	pid_t	pid;
	t_pipex	dt;

	if (ac != 5)
	{
		ft_pusage();
		ft_throw(RED "Error" RESET, "invalid argument", 0, 0);
	}
	dt.cmds = ac - 1;
	dt.cmd_id = 2;
	ft_get_mfds((char **)av, (char **)ep, &dt);
	ft_get_pths(&dt);
	pid = fork();
	if (pid < 0)
		ft_throw(RED "Fork" RESET, 0, 1, NULL);
	if (pid == 0)
		ft_pipex(&dt);
	else
		waitpid(pid, &status, 0);
	ft_free_pths(dt.pths);
	close(dt.inpf);
	close(dt.outf);
	return (WEXITSTATUS(status));
}
