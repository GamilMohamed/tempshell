/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:13:06 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 19:21:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	dstlen = 0;
	if (dst)
		dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= dstlen + 1)
		return (srclen + size);
	while (dstlen + i + 1 < size)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
