/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newexpand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:11:53 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/26 01:22:37 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dostatus(t_data *data, int *n, int *index)
{
	char	*status;

	status = ft_itoa(data->status);
	*n += ft_strlen(status);
	*index += 1;
	return (status);
}

static char	*ft_boost(char *s1, char *s2, int size)
{
	char	*temp;
	size_t	s1len;
	size_t	s2len;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = malloc(s1len + s2len + size + 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	ft_free((void **)& s1);
	return (temp);
}

static char	*getvar(t_data *data, char *str, int *n, int *index)
{
	char	*value;
	int		i;
	char	c;
	int		keylen;

	i = 1;
	if (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '?')
		return ((*n)++, "$");
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?'))
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

static char	neg(char c)
{
	if (c == DQUOTE)
		return (-c);
	return (c);
}

char	*ft_expand(t_data *data, char *s)
{
	char	*new;
	int		i;
	int		n;

	n = 0;
	i = 0;
	new = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] && s[i] == SQUOTE)
		{
			while (s[++i] && s[i] != SQUOTE)
				new[n++] = neg(s[i]);
			i++;
		}
		while (s[i] && s[i] == '$')
		{
			new[n] = '\0';
			i++;
			new = ft_boost(new, getvar(data, &s[i], &n, &i), ft_strlen(&s[i]));
		}
		if (s[i] == '\0')
			break ;
		new[n++] = s[i++];
	}
	new[n] = 0;
	return (new);
}
