/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:27:22 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/05 16:43:05 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_cmd(char *pt, char **ca, int nf, char **ep)
{
	size_t	errn;

	if (!pt)
		pt = ".";
	if (execve(pt, ca, ep) == -1)
	{
		errn = errno;
		if (nf)
		{
			ft_printf_fd(STDERR_FILENO, RED "Error %s: %s : %s\n", RESET,
				"command not found", ca[0]);
			errn = 127;
		}
		else
			ft_printf_fd(STDERR_FILENO, "Error: %s\n", strerror(errn));
		ft_free_pths(ca);
		exit(errn);
	}
}

void	ft_rd_process(int *fds, t_pipex *dt)
{
	int		nf;
	char	*cmdpt;
	char	**cmdav;

	if (dt->inpf < 0)
		return (ft_free_pths(dt->pths), ft_throw("Error", strerror(dt->errn), 0,
				dt->av[1]));
	dup2(dt->inpf, STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	cmdav = ft_split(dt->av[dt->cmd_id], ' ');
	if (!cmdav)
		ft_throw(RED "Error" RESET, "Failed to get command", 1,
			dt->av[dt->cmd_id]);
	nf = 0;
	if (access(cmdav[0], F_OK | X_OK) == 0)
		ft_exec_cmd(cmdav[0], cmdav, nf, dt->ep);
	else
	{
		cmdpt = ft_get_cmd_pth(cmdav[0], dt->pths);
		ft_free_pths(dt->pths);
		if (!cmdpt)
			nf = 1;
		ft_exec_cmd(cmdpt, cmdav, nf, dt->ep);
	}
}

void	ft_wt_process(int *fds, t_pipex *dt)
{
	int		nf;
	char	*cmdpt;
	char	**cmdav;

	dup2(fds[0], STDIN_FILENO);
	dup2(dt->outf, STDOUT_FILENO);
	cmdav = ft_split(dt->av[dt->cmd_id], ' ');
	if (!cmdav)
		ft_throw(RED "Error" RESET, "Failed to get command", 1,
			dt->av[dt->cmd_id]);
	nf = 0;
	if (cmdav[0] && access(cmdav[0], F_OK | X_OK) == 0)
		ft_exec_cmd(cmdav[0], cmdav, nf, dt->ep);
	else
	{
		cmdpt = ft_get_cmd_pth(cmdav[0], dt->pths);
		ft_free_pths(dt->pths);
		if (!cmdpt)
			nf = 1;
		ft_exec_cmd(cmdpt, cmdav, nf, dt->ep);
	}
}

void	ft_pipex(t_pipex *dt)
{
	int		status;
	pid_t	pid;
	int		pfds[2];

	if (pipe(pfds) < 0)
		ft_throw("Pipe", NULL, 1, NULL);
	pid = fork();
	if (pid < 0)
		ft_throw("Fork", NULL, 1, NULL);
	if (pid == 0)
	{
		close(pfds[0]);
		ft_rd_process(pfds, dt);
	}
	else
	{
		close(pfds[1]);
		waitpid(pid, &status, WNOHANG);
		dt->cmd_id = 3;
		ft_wt_process(pfds, dt);
	}
}

void	ft_multi_pipex(t_pipex *dt)
{
	pid_t	pid;

	while (dt->cmd_id < dt->cmds)
	{
		if (pipe(dt->pfds) < 0)
			ft_throw("Pipe", NULL, 1, NULL);
		pid = fork();
		if (pid < 0)
			ft_throw("Fork", NULL, 1, NULL);
		if (pid == 0)
		{
			close(dt->pfds[0]);
			ft_rd_process(dt->pfds, dt);
		}
		else
		{
			close(dt->pfds[1]);
			close(dt->inpf);
			dt->inpf = dt->pfds[0];
			waitpid(pid, 0, WNOHANG);
			dt->cmd_id++;
			if (dt->cmd_id == dt->cmds - 1)
				ft_wt_process(dt->pfds, dt);
		}
	}
}
