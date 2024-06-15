/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:29:17 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/15 13:28:16 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pusage(void)
{
	ft_printf_fd(STDERR_FILENO, BLUE "USAGE%s:\t- %s\n\t- %s\n", RESET,
		"./pipex <infile> cmd1 cmd2 ... cmdn <outfile>",
		"./pipex here_doc <lim> cmd1 cmd2 <outfile>");
}

void	ft_get_inpf(t_pipex *dt)
{
	int	derrn;

	if (ft_strncmp(dt->av[1], "here_doc", 8) == 0
		&& ft_strlen(dt->av[1]) == (size_t)8)
	{
		ft_create_hd(dt->av[2]);
		dt->is_hd = 1;
		dt->cmd_id = 3;
	}
	dt->inpf = open(dt->av[1], O_RDONLY, 0644);
	if (dt->inpf < 0)
	{
		derrn = errno;
		if (dt->inpf < 0 || close(dt->inpf) < 0)
			ft_printf_fd(STDERR_FILENO, RED "Error%s: %s: %s\n", RESET,
				strerror(derrn), dt->av[1]);
		dt->errn = derrn;
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

static void	ft_init_dt(char **av, char **ep, t_pipex *dt)
{
	dt->is_hd = 0;
	dt->errn = 0;
	dt->av = av;
	dt->ep = ep;
}

int	main(int ac, char const *av[], char const *ep[])
{
	int		status;
	pid_t	pid;
	t_pipex	dt;

	if (ac < 5)
	{
		ft_pusage();
		ft_throw(RED "Error" RESET, "invalid argument", 0);
	}
	dt.cmds = ac - 1;
	dt.cmd_id = 2;
	ft_init_dt((char **)av, (char **)ep, &dt);
	ft_get_pths(&dt);
	pid = fork();
	if (pid < 0)
		ft_throw(RED "Fork" RESET, strerror(errno), NULL);
	if (pid == 0)
		ft_pipex(&dt);
	else
		waitpid(pid, &status, 0);
	ft_free_pths(dt.pths);
	return (WEXITSTATUS(status));
}
