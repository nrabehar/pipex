/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:27:22 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/20 16:10:12 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_cmd(char *pt, char **ca, t_pipex *dt)
{
	size_t	errn;
	char	*cmd;

	if (!pt)
		pt = ".";
	if (execve(pt, ca, dt->ep) == -1)
	{
		cmd = ca[0];
		if (dt->xcmd)
		{
			if (!cmd)
				cmd = "";
			ft_printf_fd(STDERR_FILENO, RED "Error%s: %s: '%s'\n", RESET,
				"command not found", cmd);
			errn = 127;
		}
		ft_closes_std();
		close(dt->inpf);
		close(dt->outf);
		ft_free_pths(ca);
		exit(errn);
	}
}

static void	ft_pipe_process(t_pipex *dt)
{
	char	*cmdpt;
	char	**cmdav;

	cmdav = ft_bct_split(dt->av[dt->cmd_id]);
	if (!cmdav)
		return (ft_free_pths(dt->pths), ft_throw(RED "Error" RESET,
				strerror(errno), dt->av[dt->cmd_id]));
	dup2(dt->inpf, STDIN_FILENO);
	close(dt->inpf);
	dup2(dt->outf, STDOUT_FILENO);
	close(dt->outf);
	if (cmdav[0] && access(cmdav[0], F_OK | X_OK) == 0)
		ft_exec_cmd(cmdav[0], cmdav, dt);
	else
	{
		cmdpt = ft_get_cmd_pth(cmdav[0], dt->pths);
		ft_free_pths(dt->pths);
		if (!cmdpt)
			dt->xcmd = 1;
		ft_exec_cmd(cmdpt, cmdav, dt);
	}
}

static void	ft_waiting_process(t_pipex *dt, pid_t pid)
{
	if (ft_strncmp(dt->av[dt->cmd_id], "sleep ", 6) == 0
		|| !ft_isexist_cmd(dt->av[dt->cmd_id + 1], dt->pths))
		waitpid(pid, NULL, 0);
	else
		waitpid(pid, NULL, WNOHANG);
	close(dt->outf);
	close(dt->inpf);
	dt->inpf = dt->pfds[0];
	if (dt->is_hd && access("here_doc", F_OK) == 0 && unlink("here_doc") < 0)
		ft_throw("Here_doc", strerror(errno), 0);
	dt->cmd_id++;
	if (dt->cmd_id == dt->cmds - 1)
	{
		close(dt->pfds[1]);
		ft_get_outf(dt);
		if (dt->outf < 0)
			return (ft_free_pths(dt->pths), close(dt->inpf),
				exit(EXIT_FAILURE));
		ft_pipe_process(dt);
	}
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
			if (dt->inpf < 0)
				return (ft_free_pths(dt->pths), exit(EXIT_FAILURE));
			ft_pipe_process(dt);
		}
		else
			ft_waiting_process(dt, pid);
	}
}
