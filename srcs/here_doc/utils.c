/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:30:22 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 17:30:44 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i] && !ft_strchr("><|&", str[i])))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str)
{
	int		i;
	int		r;
	char	*new;

	new = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|&", str[i]))
		new[r++] = str[i++];
	new[r] = 0;
	return (new);
}

int	count_hd(char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				nb++;
				i++;
			}
		}
		i++;
	}
	return (nb);
}
