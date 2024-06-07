/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:58:03 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* apply `f` to all contents of list `lst` */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_clone;

	if (!lst || !f)
		return ;
	lst_clone = lst;
	while (lst_clone)
	{
		f(lst_clone->content);
		lst_clone = lst_clone->next;
	}
}
