/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 20:27:01 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/09 14:39:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t		i;
// 	char		*var;
// 	char		*temp;

// 	i = 0;
// 	var = malloc(sizeof(char) * len + 1);
// 	if (!var || s == 0)
// 		return (NULL);
// 	while ((i < start) && (s[i]))
// 		i++;
// 	if (s[i] == '\0')
// 	{
// 		free(var);
// 		return (ft_strdup(""));
// 	}
// 	i = 0;
// 	while (i < len && s[i + start])
// 	{
// 		var[i] = s[start + i];
// 		i++;
// 	}
// 	var[i] = '\0';
// 	temp = ft_strdup(var);
// 	free(var);
// 	return (temp);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	length;

	length = ft_strlen(s);
	if (start >= length || !s)
		return (str = ft_calloc(1, sizeof(char)));
	if (start + len > length)
		len = length - start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while ((i < len) && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
