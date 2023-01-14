/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:08:07 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/09 14:39:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, int size)
{
	int		i;
	char	atemp;
	char	btemp;

	i = -1;
	while (++i < size)
	{
		atemp = ((char *)a)[i];
		btemp = ((char *)b)[i];
		((char *)a)[i] = btemp;
		((char *)b)[i] = atemp;
	}
}
