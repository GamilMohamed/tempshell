/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:31:53 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/28 03:48:23 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strsubtrim(char const *str, int start, int end)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (end - start) + 2);
	if (!var)
		return (NULL);
	while (start + i <= end && str[i])
	{
		var[i] = str[start + i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*var;

	if (s == 0)
		return (NULL);
	if (*s == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s);
	i = 0;
	start = 0;
	while (s[i] && ft_isset(s[i], set))
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	start = i;
	len--;
	while (s[i] && ft_isset(s[len], set))
		len--;
	var = ft_strsubtrim(s, start, len);
	if (!var)
		return (NULL);
	return (var);
}

// int main ()
// {
// 	char *s = ft_strtrim("   xxx0123456   xxx", " x");
// 	printf("%s\n", s);
// }