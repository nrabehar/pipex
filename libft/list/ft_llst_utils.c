/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:05:34 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 21:57:43 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_llstis_empty(t_llist *llst)
{
	if (!llst)
		return (1);
	return (0);
}

int	ft_llstis_single(t_llist *llst)
{
	if (ft_llstis_empty(llst) || llst->prev)
		return (0);
	return (1);
}

int	ft_llstsize(t_llist *llst)
{
	int	size;

	size = 0;
	while (llst && ++size)
		llst = llst->next;
	return (size);
}

void	ft_llstclear(t_llist *llst)
{
	if (!llst)
		return ;
	if (llst->next)
		ft_llstclear(llst->next);
	free(llst);
	llst = NULL;
}

int	ft_llstnode_position(t_llist *node, t_llist *parent)
{
	int	pos;

	if (!parent || !node)
		return (-1);
	pos = 1;
	while (parent != node && ++pos)
		parent = parent->next;
	return (pos);
}
