/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:37:24 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 14:53:02 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_cd(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;
	int		i;

	i = -1;
	success = -1;
	if (str)
	{
		tab = ft_split(str + 2, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		while (tab[++i])
			tab[i] = invert(tab[i]);
		success = ft_cd(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

static int	builtin_export(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;
	int		i;

	i = -1;
	success = -1;
	if (str)
	{
		tab = ft_split(str + 6, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		while (tab[++i])
			tab[i] = invert(tab[i]);
		success = ft_export(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

static int	builtin_unset(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;
	int		i;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 6, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		i = -1;
		while (tab[++i])
			tab[i] = invert(tab[i]);
		success = ft_unset(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

int	builtin_exit(t_data *data, t_cmd *cmd, char *str)
{
	int		success;
	char	**tab;
	int		i;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 4, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		i = -1;
		while (tab[++i])
			tab[i] = invert(tab[i]);
		success = ft_exit(data, cmd, tab);
		ft_free_tab(tab, -1);
	}
	return (success);
}

int	ft_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd)
		return (0);
	if (!ft_strncmp(cmd->cmd, "pwd", 3))
		return (builtin_pwd(cmd->cmd), 0);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		return (builtin_echo(cmd->flags, data->env));
	if (!ft_strncmp(cmd->cmd, "env", 3))
		return (builtin_env(cmd->flags, data->env));
	if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (builtin_cd(cmd->flags, &data->env));
	if (!ft_strncmp(cmd->cmd, "export", 6))
		return (builtin_export(cmd->flags, &data->env));
	if (!ft_strncmp(cmd->cmd, "unset", 5))
		return (builtin_unset(cmd->flags, &data->env));
	if (!ft_strncmp(cmd->cmd, "exit", 4))
		return (builtin_exit(data, cmd, cmd->flags));
	return (0);
}
