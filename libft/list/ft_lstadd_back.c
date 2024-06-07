/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:59:39 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
	add node `new` in list `lst` and place it as last node.
	If the list has no nodes, the `new` is the first and only node in the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	last_node = ft_lstlast(*lst);
	if (last_node)
		last_node->next = new;
	else
		*lst = new;
}
