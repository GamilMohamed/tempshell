/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:03:16 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/25 23:06:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define HEX_BASE "0123456789abcdef"
# define U_INT unsigned int

int	ft_ptf_putnbr(int n, int *count);
int	ft_ptf_putstr(char *s);
int	ft_ptf_uiputnbr(unsigned int n, int *count);
int	ft_ptf_puthex(unsigned int nbr, char x, int *count);
int	ft_ptf_pointer(unsigned long int n, int *count);
int	ft_ptf_color(char c);
int	ft_ptf_putchar(char c);

#endif