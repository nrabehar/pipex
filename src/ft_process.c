/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:27:22 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/06 13:00:14 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_cmd(char *pt, char **ca, int nf, char **ep)
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

static void	ft_read_process(t_pipex *dt)
{
	int		nf;
	char	*cmdpt;
	char	**cmdav;

	close(dt->pfds[0]);
	if (dt->inpf < 0)
		return (ft_free_pths(dt->pths), exit(dt->errn));
	dup2(dt->inpf, STDIN_FILENO);
	dup2(dt->pfds[1], STDOUT_FILENO);
	cmdav = ft_split(dt->av[dt->cmd_id], ' ');
	if (!cmdav)
		return (ft_free_pths(dt->pths), ft_throw(RED "Error" RESET,
				strerror(errno), dt->av[dt->cmd_id]));
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

static void	ft_writte_process(t_pipex *dt)
{
	int		nf;
	char	*cmdpt;
	char	**cmdav;

	dup2(dt->inpf, STDIN_FILENO);
	dup2(dt->outf, STDOUT_FILENO);
	cmdav = ft_split(dt->av[dt->cmd_id], ' ');
	if (!cmdav)
		return (ft_free_pths(dt->pths), ft_throw(RED "Error" RESET,
				strerror(errno), dt->av[dt->cmd_id]));
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

static void	ft_waiting_process(t_pipex *dt)
{
	close(dt->pfds[1]);
	close(dt->inpf);
	dt->inpf = dt->pfds[0];
	if (dt->is_hd)
		if (unlink("here_doc") < 0)
			ft_throw("Here_doc", strerror(errno), 0);
	dt->is_hd = 0;
	dt->cmd_id++;
	if (dt->cmd_id == dt->cmds - 1)
	{
		if (dt->outf < 0)
			return (ft_free_pths(dt->pths), close(dt->inpf), ft_throw("Error",
					strerror(dt->errn), dt->av[dt->cmds]));
		ft_writte_process(dt);
	}
}

void	ft_pipex(t_pipex *dt)
{
	pid_t	pid;

	while (dt->cmd_id < dt->cmds)
	{
		if (pipe(dt->pfds) < 0)
			ft_throw("Pipe", strerror(errno), NULL);
		pid = fork();
		if (pid < 0)
			ft_throw("Fork", strerror(errno), NULL);
		if (pid == 0)
			ft_read_process(dt);
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
