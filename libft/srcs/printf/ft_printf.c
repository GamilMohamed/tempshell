/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:04:19 by mohazerr          #+#    #+#             */
/*   Updated: 2023/01/14 01:24:26 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptf_putchar(char c)
{
	if (!c)
		return (write(2, "(UNINITIALISED)", 15));
	return (write(2, &c, 1));
}

static int	ft_showarg(char c, va_list *args)
{
	int	ret;

	ret = 0;
	if (c == 'i' || c == 'd')
		ret = ft_ptf_putnbr((int)va_arg(*args, int), &ret);
	else if (c == 's')
		ret = ft_ptf_putstr((char *)va_arg(*args, char *));
	else if (c == 'c')
		ret = ft_ptf_putchar((int)va_arg(*args, int));
	else if (c == 'u')
		ret = ft_ptf_uiputnbr((U_INT)va_arg(*args, U_INT), &ret);
	else if (c == '%')
		ret = ft_ptf_putchar('%');
	else if (c == 'x' || c == 'X')
		ret = ft_ptf_puthex((U_INT)va_arg(*args, long U_INT), c, &ret);
	else if (c == 'p')
		ret = ft_ptf_pointer((long U_INT)va_arg(*args, long U_INT), &ret);
	else if (c == 'r' || c == 'g' || c == '0' || c == 'y' || c == 'm'
			|| c == 'b' || c == 'R' || c == 'G' || c == 'Y' || c == 'M'
			|| c == 'B')
		ret = ft_ptf_color(c);
	else
		ret = ft_ptf_putchar(c);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		total;
	char	*s;
	va_list	args;

	if (!format)
		return (ft_ptf_putstr("(S NULL)\n"));
	s = (char *)format;
	total = 0;
	i = 0;
	va_start(args, format);
	while (s[i])
	{
		if (s[i] != '%')
		{
			total += ft_ptf_putchar(s[i++]);
			continue ;
		}
		if (s[++i])
			total += ft_showarg(s[i], &args);
		i++;
	}
	va_end(args);
	return (total);
}

// #include <stdio.h>

// int main ()
// {
// 	// int a, b;
// 	// void *p;
// 	char *s;
// 	// a =		printf("%c%s%d%i%u%x%X %c%s%d%i%u%x%X %c%s%d%i%u%x%X %c%p\n",
// 	//  'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42,
// 	//   'C', "0", 0, 0 ,0 ,0, 42, 0, &p);
// 	// b = ft_printf("%c%s%d%i%u%x%X %c%s%d%i%u%x%X %c%s%d%i%u%x%X %c%p\n",
// 	//  'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42,
// 	//   'C', "0", 0, 0 ,0 ,0, 42, 0, &p);
// 	// int a = ft_printf("%s", 113);
// 	ft_printf("%c\n", '\n');
// 	printf("%i", printf("%i", ft_printf("13=%i\n", 13)));
// }