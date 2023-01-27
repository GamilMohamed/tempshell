/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:28:13 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 13:44:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lenof(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_stoval(t_data *data, int n)
{
	int				i;
	int				len;
	unsigned int	nb;

	nb = -(n < 0) * (n) + (n > 0) * (n);
	i = (n < 0);
	len = lenof(n);
	if (n < 0)
		data->value[0] = '-';
	data->value[len] = 0;
	while (--len >= i)
	{
		data->value[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*dostatus(t_data *data, int *n, int *index)
{
	ft_stoval(data, data->status);
	*n += ft_strlen(data->value);
	*index += 1;
	return (data->value);
}

char	*ft_boost(char *s1, char *s2, int size)
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
	temp = ft_calloc(s1len + s2len + size + 1, 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	ft_free((void **)&s1);
	return (temp);
}
