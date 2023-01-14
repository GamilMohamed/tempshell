/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:47:16 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/14 14:33:40 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *s1, char *s2)
{
	char	*temp;
	size_t	s1len;
	size_t	s2len;

	if (!s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = malloc(s1len + s2len + 1);
	ft_strcpy(temp, s1);
	ft_strcat(temp, s2);
	if (!temp)
		return (NULL);
	free(s1);
	return (temp);
}
