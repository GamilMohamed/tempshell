/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:00:18 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 19:21:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

static int	ft_nbwords(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nb_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_words);
}

static int	ft_wl(char const *s, char c, int index)
{
	int	len;

	len = 0;
	while (s[index + len] && s[index + len] != c)
		len++;
	return (len);
}

static void	*free_error_split(char **words, int wordnum)
{
	int	j;

	j = -1;
	if (words)
	{
		while (++j < wordnum)
		{
			if (words[j])
				free(words[j]);
		}
		free(words);
	}
	return (NULL);
}

static char	**ft_split_aux(char const *s, char c, int wnum)
{
	int		i;
	int		index;
	int		nb_words;
	char	**words;

	index = 0;
	nb_words = ft_nbwords(s, c);
	words = malloc(sizeof(*words) * (nb_words + 1));
	if (!words)
		return (NULL);
	while (++wnum < nb_words)
	{
		while (s[index] == c)
			index++;
		words[wnum] = malloc(sizeof(*(words[wnum])) * (ft_wl(s, c, index) + 1));
		if (!(words[wnum]))
			return (free_error_split(words, wnum));
		i = 0;
		while (s[index] && s[index] != c)
			words[wnum][i++] = s[index++];
		words[wnum][i] = '\0';
	}
	words[wnum] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_split_aux(s, c, -1));
}
