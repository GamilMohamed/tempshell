/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:14:05 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 08:40:31 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checksyntax(char *s)
{
	char	**tab;
	int		len;
	char	*temp;
	int		i;

	temp = ft_strtrim(s, " ");
	len = ft_strlen(temp);
	if (!len)
		return (free(temp), free(s), 1);
	i = -1;
	while (METACHAR[++i])
		if (METACHAR[i] == temp[len - 1])
		{
			return (free(temp), free(s), printf("bash: syntax error near unexpected token '%c'!\n",
					METACHAR[i]));
		}
	i = 1;
	while (METACHAR[++i])
		if (METACHAR[i] == temp[0])
		{
			return (free(temp), free(s), printf("bash: syntax error near unexpected token '%c'!\n",
					METACHAR[i]));
		}
	if (checkagain(temp, len))
		return (free(s), 1);
	free(temp);
	return (0);
}

int	checkquotes(char *s)
{
	int		quote;
	int		i;
	char	c;

	quote = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] != SQUOTE && s[i] != DQUOTE)
			i++;
		if (s[i] && (s[i] == SQUOTE || s[i] == DQUOTE))
		{
			c = s[i];
			if (s[i++] == c)
				quote++;
			while (s[i] && (s[i] != c))
				i++;
			if (s[i++] == c)
				quote++;
			else
				break ;
		}
	}
	if (quote % 2)
		return (printf("unclosed quotes !\n"), free(s), 1);
	return (0);
}

int	checkagain(char *temp, int len)
{
	int	i;
	int	j;

	i = 2;
	while (METACHAR[++i])
	{
		j = -1;
		while (temp[++j])
			if (temp[j] == METACHAR[i])
				return (free(temp), printf("bash: syntax error near unexpected token '%c'\n", METACHAR[i]));
	}
	// if (ft_strnstr(temp, "||", len))
	// 	return (free(temp), printf("syntax error '||' !\n"));
	// if (ft_strnstr(temp, "&&", len))
		// return (free(temp), printf("syntax error '&&' !\n"));
	return (0);
}

int	isaredirection(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	else if (!ft_strcmp(s, ">>"))
		return (2);
	else if (!ft_strcmp(s, "<"))
		return (3);
	else if (!ft_strcmp(s, "<<"))
		return (4);
	return (0);
}
