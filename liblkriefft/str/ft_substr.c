/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:07:02 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 19:21:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	i = 0;
	while (i < len && start + i < len_s)
		i++;
	dst = malloc(sizeof(*dst) * (i + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && start + i < len_s)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
