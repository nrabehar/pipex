/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:59:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/20 15:55:24 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_init_dt(int ac, char **av, char **ep, t_pipex *dt)
{
	dt->cmds = ac - 1;
	dt->cmd_id = 2;
	dt->xcmd = 0;
	dt->is_hd = 0;
	dt->errn = 0;
	dt->av = av;
	dt->ep = ep;
	if (ft_strncmp(dt->av[1], "here_doc", 8) == 0
		&& ft_strlen(dt->av[1]) == (size_t)8 && dt->cmds >= 5)
	{
		dt->is_hd = 1;
		dt->cmd_id = 3;
	}
}

int	main(int ac, char const *av[], char const *ep[])
{
	int		status;
	pid_t	pid;
	t_pipex	dt;

	if (ac != 5)
	{
		ft_printf_fd(STDERR_FILENO, BLUE "USAGE%s: %s\n", RESET,
			"./pipex <infile> cmd1 cmd2 <outfile>");
		ft_throw(RED "Error" RESET, "invalid argument", 0);
	}
	ft_init_dt(ac, (char **)av, (char **)ep, &dt);
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
