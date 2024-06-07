/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:53:57 by nrabehar          #+#    #+#             */
/*   Updated: 2024/05/02 21:57:06 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_llist	*ft_llstnew(void *content)
{
	t_llist	*list;

	list = (t_llist *)malloc(sizeof(t_llist));
	if (!list)
		return (NULL);
	list->content = content;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}

void	ft_llstadd_front(t_llist **llst, t_llist *new)
{
	if (!new)
		return ;
	if (ft_llstis_empty(*llst))
	{
		*llst = new;
		return ;
	}
	new->next = *llst;
	new->prev = (*llst)->prev;
	(*llst)->prev = new;
	*llst = new;
}

void	ft_llstadd_back(t_llist **llst, t_llist *new)
{
	if (!new)
		return ;
	if (ft_llstis_empty(*llst))
	{
		*llst = new;
		return ;
	}
	if (ft_llstis_single(*llst))
	{
		new->prev = *llst;
		(*llst)->next = new;
	}
	else
	{
		new->prev = (*llst)->prev;
		(*llst)->prev->next = new;
	}
	new->next = NULL;
	(*llst)->prev = new;
}

void	ft_llstpop_front(t_llist **llst)
{
	t_llist	*tmp_llst;

	if (!llst || !*llst)
		return ;
	if (ft_llstis_single(*llst))
	{
		free(*llst);
		*llst = NULL;
		return ;
	}
	tmp_llst = *llst;
	if (tmp_llst->next->next)
		tmp_llst->next->prev = tmp_llst->prev;
	else
		tmp_llst->next->prev = NULL;
	*llst = tmp_llst->next;
	free(tmp_llst);
	tmp_llst = NULL;
}

void	ft_llstpop_back(t_llist **llst)
{
	t_llist	*tmp_llst;

	if (!llst || !*llst)
		return ;
	if (ft_llstis_single(*llst))
	{
		free(*llst);
		*llst = NULL;
		return ;
	}
	tmp_llst = (*llst)->prev;
	tmp_llst->prev->next = NULL;
	if (tmp_llst->prev != *llst)
		(*llst)->prev = tmp_llst->prev;
	else
		(*llst)->prev = NULL;
	if (tmp_llst->next->next)
		tmp_llst->next->prev = tmp_llst->prev;
	else
		tmp_llst->next->prev = NULL;
	free(tmp_llst);
	tmp_llst = NULL;
}
