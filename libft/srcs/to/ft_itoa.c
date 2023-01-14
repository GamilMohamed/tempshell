/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:38:03 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/09 14:39:53 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nblen(int n)
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

char	*ft_itoa(int n)
{
	int				i;
	int				len;
	unsigned int	nb;
	char			*str;

	nb = -(n < 0) * (n) + (n > 0) * (n);
	i = (n < 0);
	len = ft_nblen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[len] = 0;
	while (--len >= i)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

// int main ()
// {
// 	int i;
// 	i = -1;
// 	while (i++ < 10)
// 	{
// 		printf("%i %i\n", i, i + 1);
// 	}

// 	// while (i++ < 10)
// 	// {
// 	// 	printf("%i\n", i);
// 	// }
// }