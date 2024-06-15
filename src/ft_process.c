/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:27:22 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/15 13:23:41 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_cmd(char *pt, char **ca, int nf, t_pipex *dt)
{
	size_t	errn;

	if (!pt)
		pt = ".";
	if (nf)
	{
		ft_printf_fd(STDERR_FILENO, RED "Error %s: %s : %s\n", RESET,
			"command not found", ca[0]);
		errn = 127;
		dup2(STDIN_FILENO, dt->inpf);
		dup2(STDOUT_FILENO, dt->outf);
		if (dt->pfds[0] != dt->inpf)
			close(dt->pfds[0]);
		if (dt->pfds[1] != dt->outf)
			close(dt->pfds[1]);
		close(dt->outf);
		close(dt->inpf);
	}
	if (execve(pt, ca, dt->ep) == -1 && nf == 0)
	{
		errn = errno;
		ft_printf_fd(STDERR_FILENO, "Error: %s\n", strerror(errn));
	}
	ft_free_pths(ca);
	exit(errn);
}

static void	ft_pipe_process(t_pipex *dt)
{
	int		nf;
	char	*cmdpt;
	char	**cmdav;

	cmdav = ft_split(dt->av[dt->cmd_id], ' ');
	if (!cmdav)
		return (ft_free_pths(dt->pths), ft_throw(RED "Error" RESET,
				strerror(errno), dt->av[dt->cmd_id]));
	dup2(dt->inpf, STDIN_FILENO);
	dup2(dt->outf, STDOUT_FILENO);
	nf = 0;
	if (cmdav[0] && access(cmdav[0], F_OK | X_OK) == 0)
		ft_exec_cmd(cmdav[0], cmdav, nf, dt);
	else
	{
		cmdpt = ft_get_cmd_pth(cmdav[0], dt->pths);
		ft_free_pths(dt->pths);
		if (!cmdpt)
			nf = 1;
		ft_exec_cmd(cmdpt, cmdav, nf, dt);
	}
}

static void	ft_waiting_process(t_pipex *dt)
{
	close(dt->pfds[1]);
	close(dt->inpf);
	dt->inpf = dt->pfds[0];
	if (dt->is_hd > 0)
		if (unlink("here_doc") < 0)
			ft_throw("Here_doc", strerror(errno), 0);
	if (dt->is_hd)
		dt->is_hd = -1;
	else
		dt->is_hd = 0;
	dt->cmd_id++;
	if (dt->cmd_id == dt->cmds - 1)
	{
		ft_get_outf(dt);
		if (dt->outf < 0)
			return (ft_free_pths(dt->pths), close(dt->inpf), ft_throw("Error",
					strerror(dt->errn), dt->av[dt->cmds]));
		ft_pipe_process(dt);
	}
}

static void	ft_check_inpf(t_pipex *dt)
{
	close(dt->pfds[0]);
	if (dt->inpf < 0)
		return (ft_free_pths(dt->pths), exit(dt->errn));
}

void	ft_pipex(t_pipex *dt)
{
	pid_t	pid;

	ft_get_inpf(dt);
	while (dt->cmd_id < dt->cmds)
	{
		if (pipe(dt->pfds) < 0)
			ft_throw("Pipe", strerror(errno), NULL);
		dt->outf = dt->pfds[1];
		pid = fork();
		if (pid < 0)
			ft_throw("Fork", strerror(errno), NULL);
		if (pid == 0)
		{
			ft_check_inpf(dt);
			ft_pipe_process(dt);
		}
		else
		{
			if (ft_strncmp(dt->av[dt->cmd_id], "sleep", 5) == 0)
				wait(NULL);
			else
				waitpid(pid, NULL, WNOHANG);
			ft_waiting_process(dt);
		}
	}
}
