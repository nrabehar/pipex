/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:59:12 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/19 14:56:51 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

# define RED "\e[31m"
# define BLUE "\e[34m"
# define RESET "\e[0m"

typedef struct s_pipex
{
	int		inpf;
	int		outf;
	int		pfds[2];
	int		cmds;
	int		xcmd;
	int		errn;
	int		cmd_id;
	int		is_hd;
	char	**av;
	char	**ep;
	char	**pths;
}			t_pipex;

void		ft_throw(char const *title, char *m, char const *pt);
void		ft_free_pths(char **pths);
void		ft_get_pths(t_pipex *dt);
void		ft_get_inpf(t_pipex *dt);
void		ft_get_outf(t_pipex *dt);
void		ft_closes_std(void);
void		ft_create_hd(char const *delimiter);
char		*ft_get_cmd_pth(char *cmd, char **pths);
int			ft_isexist_cmd(char *cmd, char **pths);
int			ft_issleep_cmd(char *cmd);
void		ft_pipex(t_pipex *dt);

#endif //! PIPEX_H