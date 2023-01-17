/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/17 00:44:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **tab, char ***addr_ev)
{
	int	n;

	while (tab && *tab)
	{
		n = ft_ev_getvarindex(*tab, *addr_ev);
		if (n >= 0)
			*addr_ev = regenerate_ev(ft_tablen(*addr_ev) - 1, n, *addr_ev);
		tab++;
	}
	return (1);
}
