/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:35:31 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/16 22:09:37 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		y;
	int		x;

	x = -1;
	y = -1;
	if (s1 == 0)
		return (NULL);
	new = malloc(ft_gnl_strlen((char *)s1) + ft_gnl_strlen((char *)s2) + 1);
	if (!new)
		return (NULL);
	while (s1[++x])
		new[x] = s1[x];
	while (s2[++y])
		new[x + y] = s2[y];
	new[x + y] = '\0';
	return (new);
}

void	*ft_gnl_calloc(size_t n)
{
	char	*new;
	size_t	i;

	i = -1;
	new = malloc(n);
	if (!new)
		return (NULL);
	while (++i < n)
		new[i] = '\0';
	return (new);
}

char	*ft_gnl_strchr(char *s, char x)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == x)
			return (&s[i]);
		i++;
	}
	return (NULL);
}
