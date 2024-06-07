/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:52:31 by nrabehar          #+#    #+#             */
/*   Updated: 2024/04/17 11:23:13 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LLST_H
# define FT_LLST_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_llist
{
	void			*content;
	struct s_llist	*prev;
	struct s_llist	*next;
}					t_llist;

/* utils */
bool				ft_llstis_empty(t_llist *llst);
bool				ft_llstis_single(t_llist *llst);
int					ft_llstsize(t_llist *llst);
int					ft_llstnode_position(t_llist *node, t_llist *parent);

t_llist				*ft_llstnew(void *content);
void				ft_llstadd_front(t_llist **llst, t_llist *new);
void				ft_llstadd_back(t_llist **llst, t_llist *new);
void				ft_llstpop_front(t_llist **llst);
void				ft_llstpop_back(t_llist **llst);
void				ft_llstclear(t_llist *llst);

#endif //! FT_LLST_H