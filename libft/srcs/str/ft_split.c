/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:11:13 by mohazerr          #+#    #+#             */
/*   Updated: 2023/01/28 01:33:07 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	freeloop(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_countdelim(char const *str, char *charset)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str && str[i])
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		counter++;
		while (str[i] && !ft_strchr(charset, str[i]))
			i++;
	}
	return (counter);
}

char	*ft_strtsub(char const *str, int start, int end)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * end - start + 1);
	if (!var)
		return (NULL);
	while (((start + i) < end) && str[i])
	{
		var[i] = str[start + i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	**to_tab(char **tab, char const *s, char *charset, int count)
{
	int	i;
	int	index;
	int	start;

	i = 0;
	index = 0;
	while (index < count)
	{
		while (s[i] && ft_strchr(charset, s[i]))
			i++;
		start = i;
		while (s[i] && (!ft_strchr(charset, s[i])))
			i++;
		tab[index] = ft_strtsub(s, start, i);
		if (!tab[index])
		{
			freeloop(tab);
			return (NULL);
		}
		index++;
	}
	return (tab);
}

char	**ft_split(char const *s, char *charset, int *size)
{
	char	**tab;

	if (!s || !*s)
		return (ft_calloc(sizeof(char *) * 1, 1));
	*size = ft_countdelim(s, charset);
	tab = ft_calloc(sizeof(char *) * (*size + 1), 1);
	if (!tab)
		return (NULL);
	tab = to_tab(tab, s, charset, *size);
	*(tab + *size) = NULL;
	return (tab);
}
