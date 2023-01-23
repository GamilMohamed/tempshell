/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:30:30 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/22 20:51:01 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(int s, int t, ...)
{
	int i;
	va_list	list;

	va_start(list, t);
	i = -1;
	while (++i < s)
		ft_free((void **)va_arg(list, void **));
	i = -1;
	while (++i < t)
		ft_freetab((char **)va_arg(list, char **));
	va_end(list);
}
