/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newexpand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:11:53 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 13:45:14 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getvar(t_data *data, char *str, int *n, int *index)
{
	char	*value;
	int		i;
	char	c;
	int		keylen;

	i = 1;
	if (ft_isdigit(str[0]))
		return ((*index)++, "");
	if (!ft_isalpha(str[0]) && str[0] != '_' && str[0] != '?')
		return ((*n)++, "$");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	c = str[i];
	str[i] = '\0';
	if (*str == '?' && *(str + 1) != '?')
		return (str[i] = c, dostatus(data, n, index));
	keylen = ft_strlen(str);
	value = ft_ev_getvar(str, data->env);
	*index += keylen;
	str[i] = c;
	if (!value)
		return ("");
	*n += ft_strlen(value + keylen) - 1;
	return (value + keylen + 1);
}

static void	singlequote(char *new, char *s, int *i, int *n)
{
	(*i)++;
	while (s[*i] && s[*i] != SQUOTE)
		new[(*n)++] = s[(*i)++];
	(*i)++;
}

static int	doublequote(char **tab[2], int *i, int *n, t_data *data)
{
	(*i)++;
	while ((*tab)[1][*i] && (*tab)[1][*i] != DQUOTE)
	{
		while ((*tab)[1][*i] && (*tab)[1][*i] == '$')
		{
			(*tab)[0][*n] = '\0';
			(*i)++;
			(*tab)[0] = ft_boost((*tab)[0], getvar(data, &(*tab)[1][*i], n, i),
					ft_strlen(&(*tab)[1][*i]));
		}
		if ((*tab)[1][*i] && (*tab)[1][*i] != DQUOTE)
			(*tab)[0][(*n)++] = (*tab)[1][(*i)++];
	}
	if ((*tab)[1][*i] == '\0')
		return (1);
	(*i)++;
	return (0);
}

char	*ft_expand(t_data *data, char *s)
{
	char	*new;
	int		i;
	int		n;

	n = 0;
	i = 0;
	new = ft_calloc(ft_strlen(s) + 1, 1);
	if (!new)
		return (ft_puterror(FAILED_MALLOC, "ft_expand"));
	while (s[i])
	{
		if (s[i] && s[i] == SQUOTE)
			singlequote(new, s, &i, &n);
		if (s[i] && s[i] == DQUOTE)
			if (doublequote((char **[2]){&new, &s}, &i, &n, data))
				break ;
		while (s[i] && s[i] == '$')
		{
			i++;
			new = ft_boost(new, getvar(data, &s[i], &n, &i), ft_strlen(&s[i]));
		}
		if (s[i])
			new[n++] = s[i++];
	}
	return (new);
}
