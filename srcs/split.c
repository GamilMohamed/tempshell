/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:11:13 by mohazerr          #+#    #+#             */
/*   Updated: 2023/01/24 03:57:01 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../libft/includes/libft.h"

#define SPACE ' '
#define SQUOTE '\''
#define DQUOTE '\"'
#include <stdio.h>

char	*get_next_line(int fd)
{
	int		i;
	int		rd;
	char	character;
	char	buffer[10000];

	i = 0;
	rd = 0;
	while ((rd = read(fd, &character, 1)) > 0)
	{
		if (character == '\n')
			break ;
		buffer[i++] = character;
	}
	if (i == 0)
		return (NULL);
	if ((!buffer[i - 1] && !rd) || rd == -1)
		return (NULL);
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

// static char	**ft_stripchar(char **tab, int count)
// {
// 	char	**new;
// 	char	quote;
// 	int		i;
// 	int		j;
// 	int		r;

// 	new = malloc(sizeof(char *) * (count + 1)); // check malloc
// 	i = -1;
// 	while (tab[++i])
// 	{
// 		r = 0;
// 		j = -1;
// 		quote = 0;
// 		while (tab[i][++j])
// 		{
// 			if (ft_checkchars(tab[i][j], SPACE, SQUOTE, DQUOTE) > 1 && !quote)
// 				quote = tab[i][j];
// 			if (tab[i][j] != quote)
// 				r++;
// 		}
// 		new[i] = ft_whichchar(tab[i], r, quote); // check malloc
// 	}
// 	ft_freetab(tab);
// 	new[i] = 0;
// 	return (new);
// }

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
		j = 0;
		quote = 0;
		while (tab[i][j])
		{
			if (ft_checkchars(tab[i][j], SPACE, SQUOTE, DQUOTE) > 1 && !quote)
				quote = tab[i][j];
			printf("quote=%c\n", quote);
			if (tab[i][j] == quote)
			{
				j++;
				while (tab[i][j] != quote)
				{
					j++;
					r++;
				}
				j++;
			}
			j++;
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

void	ft_invert(char **tab)
{
	for (size_t i = 0; tab[i]; i++)
	{
		for (size_t j = 0; tab[i][j]; j++)
		{
			if (tab[i][j] < 0)
				tab[i][j] *= -1;
		}

	}


}

char	*ft_print(char *str)
{
	int	i;
	int	r;
	int	quote;

	i = 0;
	r = 0;
	quote = 0;
	char *new = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		while (str[i] && str[i] == SQUOTE || str[i] == DQUOTE)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (ft_strchr("\t\v\n ", str[i]))
					str[i] = -str[i];
				new[r++] = str[i++];
			}
			i++;
		}
		new[r++] = str[i++];
	}
	new[r] = 0;
	char *ret = ft_strdup(new);
	free(new);
	return (ret);
}

// int	main(int ac, char **av)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = get_next_line(0);
// 	while (str)
// 	{
// 		char *new = ft_print(ft_strdup(str));
// 		char **tab = ft_split(new, ' ');
// 		ft_printtab(tab);
// 		ft_invert(tab);
// 		printf("invert->\n");
// 		ft_printtab(tab);
// 		str = get_next_line(0);
// 	}
// }

// int	main(int ac, char **av)
// {
// 	char	**tab;
// 	char	**new;
// 	char	*charset;
// 	char	*test;
// 	int counter;

// 	test = get_next_line(0);
// 	while (test)
// 	{
// 		tab = ft_splitex(test);
// 		for (int i = 0; tab[i]; i++)
// 			printf("tab[%i][%s]\n", i, tab[i]);
// 		new = ft_stripchar(tab, count(test));
// 		printf("\n");
// 		for (int i = 0; new[i]; i++)
// 			printf("new[%i][%s]\n", i, new[i]);
// 		test = get_next_line(0);
// 	}
// }
