/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:47:54 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/26 15:40:27 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_sorted_ev(char **ev)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	while (ev && ev[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(ev[j], ev[j + 1]) > 0)
				ft_swap_ev(ev, j, j + 1);
			j++;
		}
		i++;
	}
	return (ev);
}

int	ft_display_ordered_ev(char **ev)
{
	int		i;
	int		j;
	int		quotes_trigger;

	ev = ft_sorted_ev(ev);
	i = 0;
	while (ev && ev[i])
	{
		j = 0;
		while (ev[i][j] && ev[i][j] != '=')
			ft_putchar_fd(ev[i][j++], STDOUT_FILENO);
		quotes_trigger = (ev[i][j] == '=');
		if (ev[i][j] == '=')
			ft_putchar_fd(ev[i][j++], STDOUT_FILENO);
		if (quotes_trigger)
			ft_putchar_fd('"', STDOUT_FILENO);
		while (ev[i][j])
			ft_putchar_fd(ev[i][j++], STDOUT_FILENO);
		if (quotes_trigger)
			ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (1);
}

int	export_check_valid_name(char *str)
{
	char	*begin;

	begin = str;
	while (ft_isalpha(*str) || *str == '_')
		str++;
	if (str != begin)
	{
		while (ft_isalnum(*str) || *str == '_')
			str++;
		if (*str == '\0' || *str == '=')
			return (0);
	}
	ft_puterror(ERROR_EXPORT_BUILTIN, (char *)begin);
	return (1);
}

int	ft_export_var(char *str, char ***addr_ev)
{
	char	*var_name;
	char	*var;

	var_name = str;
	if (export_check_valid_name(var_name))
		return (-1);
	str = ft_strchr(str, '=');
	if (str)
		*(str++) = '\0';
	var = ft_ev_getvar(var_name, *addr_ev);
	if (!var)
		ft_ev_setvar(var_name, str, addr_ev);
	else if (var && str)
		ft_ev_setvar(var_name, str, addr_ev);
	return (1);
}

int	ft_export(char **av, char ***addr_ev)
{
	int		i;
	int		ret;
	char	*str;

	if (!*addr_ev)
		return (-1);
	if (av == NULL || av[0] == NULL)
		return (ft_display_ordered_ev(*addr_ev));
	else
	{
		ret = 0;
		i = -1;
		while (av[++i])
			ret += ft_export_var(av[i], addr_ev);
	}
	return (ret);
}
