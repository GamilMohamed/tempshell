/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:30:30 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 17:50:54 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freestruct(t_data *data)
{
	int	i;

	i = -1;
	if (!data->nb_here)
		return ;
	while (++i < data->nb_here)
		ft_free((void **)&data->here[i].delim);
	ft_free((void **)&data->here);
}

void	free_all(int s, int t, ...)
{
	int		i;
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
