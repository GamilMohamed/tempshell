/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:53:28 by mgamil            #+#    #+#             */
/*   Updated: 2022/12/25 23:04:36 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptf_color(char c)
{
	int	ret;

	if (c == '0')
		ret = ft_ptf_putstr("\033[0m");
	else if (c == 'r')
		ret = ft_ptf_putstr("\033[0;31m");
	else if (c == 'g')
		ret = ft_ptf_putstr("\033[0;32m");
	else if (c == 'b')
		ret = ft_ptf_putstr("\033[0;34m");
	else if (c == 'y')
		ret = ft_ptf_putstr("\033[0;93m");
	else if (c == 'm')
		ret = ft_ptf_putstr("\033[0;95m");
	else if (c == 'R')
		ret = ft_ptf_putstr("\033[0;41m");
	else if (c == 'G')
		ret = ft_ptf_putstr("\033[0;42m");
	else if (c == 'B')
		ret = ft_ptf_putstr("\033[0;44m");
	else if (c == 'Y')
		ret = ft_ptf_putstr("\033[0;103m");
	else
		ret = ft_ptf_putstr("\033[0;105m");
	return (ret);
}
