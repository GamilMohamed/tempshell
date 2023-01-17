/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:00:18 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/16 18:27:38 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

void	*ft_free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (tab && tab[i] && (i < n || n < 0))
		free(tab[i++]);
	if (tab)
		free(tab);
	return (NULL);
}