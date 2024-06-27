/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrabehar <nrabehar@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:38:00 by nrabehar          #+#    #+#             */
/*   Updated: 2024/06/18 15:45:45 by nrabehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_tab(void **tab)
{
	int	i;

	i = 0;
	while (((unsigned char **)tab)[i])
		free(((unsigned char **)tab)[i]);
	free(tab);
}
