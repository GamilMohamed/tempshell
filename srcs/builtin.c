/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:37:24 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/26 03:19:07 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_env(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		fprintf(stdout, "%s\n", env[i]);
	return (1);
}

static char	*builtin_echo_expand(char *str, char **env)
{
	int		i;
	char	*s;
	int		fd;

	if (str[0] != '$')
		return (str);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(str + 1, env[i], ft_strlen(str) - 1))
			return (env[i] + ft_strlen(str));
	}
	ft_printf("pas trouve\n");
	return (str);
}

static int	builtin_echo_opt(char **tab, int *opt)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (tab[++i])
	{
		j = 0;
		if (tab[i][j] != '-')
			return (k);
		else
		{
			j++;
			while (tab[i][j] == 'n')
				j++;
			if (tab[i][j] == '\0')
				*opt = ++k;
			else
				return (k);
		}
	}
	return (k);
}

static int	builtin_echo(char *s, char **env)
{
	char	**tab;
	int		i;
	int		opt;

	opt = 0;
	tab = ft_split(s, ' ');
	i = builtin_echo_opt(tab, &opt);
	while (tab[++i])
	{
		if (tab[i + 1])
			printf("%s ", tab[i]);
		else
			printf("%s", tab[i]);
	}
	if (!opt)
		printf("\n");
	ft_freetab(tab);
	return (1);
}

char	*builtin_pwd(char *s)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) == NULL)
		printf("error: %s", strerror(errno));
	else if (s)
	{
		printf("%s\n", buff);
		return (NULL);
	}
	return (ft_strdup(buff));
}

static int	builtin_cd(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 2, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		success = ft_cd(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

static int	builtin_export(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 6, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		success = ft_export(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

static int	builtin_unset(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 6, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC, NULL), -1);
		success = ft_unset(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

int	ft_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd->cmd)
		return (0);
	if (!ft_strncmp(cmd->cmd, "pwd", 3))
		return (builtin_pwd(cmd->cmd), 1);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		return (builtin_echo(cmd->flags, data->env), 1);
	if (!ft_strncmp(cmd->cmd, "env", 3))
		return (builtin_env(cmd->flags, data->env), 1);
	if (!ft_strncmp(cmd->cmd, "cd", 3))
		return (builtin_cd(cmd->flags, &data->env), 1);
	if (!ft_strncmp(cmd->cmd, "export", 6))
		return (builtin_export(cmd->flags, &data->env), 1);
	if (!ft_strncmp(cmd->cmd, "unset", 5))
		return (builtin_unset(cmd->flags, &data->env), 1);
	// if (!ft_strcmp(cmd->cmd, "exit"))
	// return (, exit(1), 1);
	return (0);
}
