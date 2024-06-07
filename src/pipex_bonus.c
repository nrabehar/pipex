/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:29:17 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:42 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pusage(void)
{
	ft_printf_fd(STDERR_FILENO, BLUE "USAGE%s: - %s\n\t - %s\n", RESET,
		"<infile> cmd1 cmd2 ... cmdn <outfile>",
		"here_doc <lim> cmd1 cmd <outfile>");
}

static int	ft_get_inpf(t_pipex *dt)
{
	int	inpf_fd;

	if (ft_strncmp(dt->av[1], "here_doc", 9) == 0
		&& ft_strlen(dt->av[1]) == (size_t)9)
	{
		ft_create_hd(dt->av[2]);
		dt->is_hd = 1;
		dt->cmd_id = 3;
		dt->inpf = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
		dt->inpf = open(dt->av[1], O_RDONLY, 0644);
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
	dt->av = av;
	dt->ep = ep;
	dt->inpf = ft_get_inpf(dt->av[1]);
	dt->outf = ft_get_outf(dt->av[dt->cmds], dt->inpf);
}

int	main(int ac, char const *av[], char const *ep[])
{
	int		status;
	pid_t	pid;
	t_pipex	dt;

	if (ac < 5)
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
		ft_multi_pipex(&dt);
	else
		waitpid(pid, &status, 0);
	ft_free_pths(dt.pths);
	close(dt.inpf);
	close(dt.outf);
	return (WEXITSTATUS(status));
}
