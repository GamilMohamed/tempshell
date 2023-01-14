/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:11:13 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/28 02:31:21 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char	*ft_whichchar(char *tab, int r, char quote)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (r + 1)); // check malloc
	j = -1;
	i = 0;
	while (tab[++j])
	{
		if (tab[j] != quote)
			new[i++] = tab[j];
	}
	new[i] = 0;
	return (new);
}

static char	**ft_stripchar(char **tab, int count)
{
	char	**new;
	char	quote;
	int		i;
	int		j;
	int		r;

	new = malloc(sizeof(char *) * (count + 1)); // check malloc
	i = -1;
	while (tab[++i])
	{
		r = 0;
		j = -1;
		quote = 0;
		while (tab[i][++j])
		{
			if (ft_checkchars(tab[i][j], SPACE, SQUOTE, DQUOTE) > 1 && !quote)
				quote = tab[i][j];
			if (tab[i][j] != quote)
				r++;
		}
		new[i] = ft_whichchar(tab[i], r, quote); // check malloc
	}
	ft_freetab(tab);
	new[i] = 0;
	return (new);
}

static int	count(char const *str)
{
	int		i;
	int		counter;
	char	quote;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) == 1)
			i++;
		if (str[i] == '\0')
			break ;
		while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) == 0)
			i++;
		if (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) > 1)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) != 1)
				i++;
		}
		counter++;
	}
	return (counter);
}

static char	**to_tab(char **tab, char const *str, int count)
{
	int		i;
	int		index;
	int		start;
	char	quote;

	i = 0;
	index = 0;
	while (index < count)
	{
		while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) == 1)
			i++;
		start = i;
		while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) == 0)
			i++;
		if (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) > 1)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			while (str[i] && ft_checkchars(str[i], SPACE, SQUOTE, DQUOTE) != 1)
				i++;
		}
		tab[index] = ft_substr(str, start, i - start);
		if (!tab[index++])
			return (ft_freetab(tab), NULL);
	}
	return (tab);
}

char	**ft_splitex(char const *s)
{
	int		nb;
	char	**tab;

	if (s == 0)
		return (NULL);
	nb = count(s);
	tab = malloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	tab = to_tab(tab, s, nb); // check malloc
	tab[nb] = NULL;
	tab = ft_stripchar(tab, nb);
	return (tab);
}
// for (size_t i = 0; tab[i]; i++)
// ft_printf("[%i]={%s}\n", i, tab[i]);

// int	main(int ac, char **av)
// {
// 	char	**tab;
// 	char	**new;
// 	char	*charset;
// 	char	*test;
// 	int counter;

// 	charset = malloc(sizeof(char) * 3);
// 	charset[0] = c ==
// 	charset[1] = '\'';
// 	charset[2] = '\0';
// 	if (ac != 2)
// 		exit(1);
// 	test = ft_strdup(av[1]);
// 	tab = ft_splitex(test, &counter);
// 	for (int i = 0; tab[i]; i++)
// 		printf("[%s]", tab[i]);
// 	new = ft_stripchar(tab, counter, '\'');
// 	printf("\n");
// 	for (int i = 0; new[i]; i++)
// 		printf("[%s]", new[i]);
// 	// printf("[%s]", ft_strtrim(tab[i], ""));
// }
