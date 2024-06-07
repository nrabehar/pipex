/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:43:37 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 17:35:58 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
	Get the number of nodes in the list starting with the first `lst` node
*/

int	ft_lstsize(t_list *lst)
{
	t_list	*lst_tmp;
	int		size;

	lst_tmp = lst;
	size = 0;
	while (lst_tmp)
	{
		size++;
		lst_tmp = lst_tmp->next;
	}
	return (size);
}
