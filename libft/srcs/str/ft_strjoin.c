/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 21:48:22 by mohazerr          #+#    #+#             */
/*   Updated: 2023/01/03 03:25:16 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	int		y;
	int		x;
	char	*new;

	x = 0;
	y = 0;
	if (s1 == 0)
		return (NULL);
	total = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new = malloc(sizeof(char) * total + 1);
	if (!new)
		return (NULL);
	while (s1[x])
	{
		new[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		new[x + y] = s2[y];
		y++;
	}
	new[x + y] = '\0';
	return (new);
}
