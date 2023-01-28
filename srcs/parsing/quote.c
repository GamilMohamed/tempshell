/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:20:23 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/28 01:36:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	ft_quoteutils(char *str, char *new, int *i, int *r)
{
	int	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (ft_strchr("\t\v\n >|&)(<", str[*i]))
			str[*i] = -str[*i];
		new[(*r)++] = str[(*i)++];
	}
	if (!str[*i])
		return (1);
	(*i)++;
	return (0);
}

char	*ft_quote(char *str)
{
	int		i;
	int		r;
	int		quote;
	char	*new;
	char	*ret;

	i = 0;
	r = 0;
	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
		return (ft_puterror(FAILED_MALLOC, "ft_quote"));
	while (str[i])
	{
		while (str[i] && (str[i] == SQUOTE || str[i] == DQUOTE))
		{
			if (ft_quoteutils(str, new, &i, &r))
				break;
		}
		if (!str[i])
			break ;
		new[r++] = str[i++];
	}
	new[r] = 0;
	ret = ft_strdup(new);
	free_all(2, 0, &new, &str);
	return (ret);
}
