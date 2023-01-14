/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:50:04 by mohazerr          #+#    #+#             */
/*   Updated: 2022/12/25 23:04:36 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptf_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		ft_ptf_putchar(s[i++]);
	return (i);
}

int	ft_ptf_putnbr(int n, int *count)
{
	long int	nbr;

	nbr = n;
	if (n < 0)
	{
		nbr *= -1;
		*count = 1;
		ft_ptf_putchar('-');
	}
	if (nbr > 9)
		ft_ptf_putnbr((nbr / 10), count);
	ft_ptf_putchar((nbr % 10) + '0');
	return (*count += 1);
}

int	ft_ptf_uiputnbr(unsigned int n, int *count)
{
	if (n > 9)
		ft_ptf_putnbr((n / 10), count);
	ft_ptf_putchar((n % 10) + '0');
	return (*count += 1);
}

int	ft_ptf_puthex(unsigned int n, char x, int *count)
{
	char				*base_x;
	char				*base_ux;

	base_x = HEX_BASE;
	base_ux = "0123456789ABCDEF";
	if (n >= 16)
		ft_ptf_puthex((n / 16), x, count);
	if (x == 'X')
		ft_ptf_putchar(base_ux[(n % 16)]);
	else
		ft_ptf_putchar(base_x[(n % 16)]);
	return (*count += 1);
}

int	ft_ptf_pointer(unsigned long int n, int *count)
{
	char	*base_x;

	base_x = HEX_BASE;
	if (n == 0)
		return (*count = ft_ptf_putstr("(nil)"));
	if (*count == 0)
		*count += ft_ptf_putstr("0x");
	if (n >= 16)
		ft_ptf_pointer((n / 16), count);
	ft_ptf_putchar(base_x[(n % 16)]);
	return (*count += 1);
}
