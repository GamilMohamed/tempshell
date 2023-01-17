/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:37:24 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/17 02:01:26 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_env(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
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
		if (!ft_strncmp(str + 1, env[i], ft_strlen(str) - 1)) // $ARG, ARG, 4
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

	i = 0;
	opt = 0;
	tab = ft_splitex(s); // check malloc
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
	char	*str;
	char	*temp;
	int		ret;
	int		i;

	i = 1;
	str = ft_calloc(i, 1); // check malloc
	while (1)
	{
		if (getcwd(str, i))
			break ;
		else
		{
			free(str);
			str = ft_calloc(i + 1, 1);
			if (!str)
				return (NULL);
		}
		i++;
	}
	if (s)
		printf("%s\n", str);
	return (str);
}

static int	builtin_cd(char *str, char ***addr_ev)
{
	int		success;
	char	**tab;

	success = -1;
	if (str)
	{
		tab = ft_split(str + 3, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC), -1);
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
		tab = ft_split(str + 7, ' ');
		if (!tab)
			return (ft_puterror(FAILED_MALLOC), -1);
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
			return (ft_puterror(FAILED_MALLOC), -1);
		success = ft_unset(tab, addr_ev);
		ft_free_tab(tab, -1);
	}
	return (success);
}

int	ft_builtin(char *s, char **env, char ***addr_env)
{
	char *temp;

	temp = ft_strtrim(s, " ");
	if (!ft_strcmp(temp, "pwd"))
		return (builtin_pwd(temp), free(temp), 1);
	if (!ft_strncmp(temp, "echo", 4))
		return (builtin_echo(temp, env), free(temp), 1);
	// if (!ft_strcmp(temp, "echo"))
		// return (ft_printf("\n"));
	if (!ft_strcmp(temp, "env"))
		return (builtin_env(temp, env), free(temp), 1);
	if (!ft_strncmp(temp, "cd ", 3) || !ft_strcmp(temp, "cd"))
		return (builtin_cd(temp, addr_env), free(temp), 1);
	if (!ft_strncmp(temp, "export ", 7) || !ft_strcmp(temp, "export"))
		return (builtin_export(temp, addr_env), free(temp), 1);
	if (!ft_strncmp(temp, "unset ", 6))
		return (builtin_unset(temp, addr_env), free(temp), 1);
	if (!ft_strcmp(temp, "exit"))
		return (free(temp), free(s), exit(1), 1);
	free(temp);
	return (0);
}