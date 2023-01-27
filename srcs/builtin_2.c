/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:23:45 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/27 14:52:48 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		fprintf(stdout, "%s\n", env[i]);
	return (1);
}

char	*builtin_echo_expand(char *str, char **env)
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

int	builtin_echo_opt(char **tab, int *opt)
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

int	builtin_echo(char *s, char **env)
{
	char	**tab;
	int		i;
	int		opt;
	int		r;

	r = -1;
	opt = 0;
	tab = ft_split(s, ' ');
	while (tab[++r])
		tab[r] = invert(tab[r]);
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
	return (0);
}

char	*builtin_pwd(char *s)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) == NULL)
		return (ft_strdup(""));
	else if (s)
	{
		printf("%s\n", buff);
		return (NULL);
	}
	return (ft_strdup(buff));
}
