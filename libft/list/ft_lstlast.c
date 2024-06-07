/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:47:17 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
	get the last node of the `lst` list.
	create a clone of the list so as not to modify the original list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_clone;

	if (!lst)
		return (NULL);
	lst_clone = lst;
	while (lst_clone->next)
		lst_clone = lst_clone->next;
	return (lst_clone);
}
