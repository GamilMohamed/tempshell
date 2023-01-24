/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:50:36 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 21:58:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenv_env(char *s, char **env)
{
	int i = 0;
	int len;
	len = ft_strlen(s);
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, len))
		{
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	return (NULL);
}

int	ft_checkdollar(char *s, int *total, char *string, char **env)
{
	int		i;
	char	*str;
	char	*new;
	int		j;

	i = 1;
	while (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
		i++;
	str = ft_substr(s, 1, i - 1);
	new = getenv_env(str, env);
	if (!*str)
	{
		ft_strcat(string, "$");
		*total += 1;
	}
	if (new)
	{
		*total += ft_strlen(new);
		ft_strcat(string, new);
	}
	free(new);
	free(str);
	return (i);
}

int	ft_expandsize(char *s, char **env)
{
	int		i;
	int		total;

	total = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == '$')
			i += ft_checkdollar(&s[i], &total, NULL, env);
		if (s[i] == '\0')
			break ;
		if (s[i] && s[i] == SQUOTE)
		{
			i++;
			total++;
			while (s[i] && s[i] != SQUOTE)
			{
				i++;
				total++;
				if (s[i] == '\0')
					break ;
			}
			total++;
			i++;
		}
		if (s[i] && s[i] == DQUOTE)
		{
			total++;
			i++;
			while (s[i] && s[i] == '$')
				i += ft_checkdollar(&s[i], &total, NULL, env);
			if (s[i] == '\0')
				break ;
			while (s[i] && s[i] != DQUOTE)
			{
				while (s[i] && s[i] == '$')
					i += ft_checkdollar(&s[i], &total, NULL, env);
				if (s[i] == '\0')
					break ;
				total++;
				i++;
			}
			if (s[i] == '\0')
					break ;
			total++;
			i++;
		}
		if (s[i] == '\0')
			break ;
		total++;
		i++;
	}
	return (total);
}

char	*ft_expand(char *s, char **env)
{
	int		i;
	int		len;
	char	*new;
	int		total;
	char	*str;

	total = 0;
	i = 0;
	len = ft_expandsize(s, env);
	str = ft_calloc(len + 1, 1);
	while (s[i])
	{
		while (s[i] && s[i] == '$')
			i += ft_checkdollar(&s[i], &total, str, env);
		if (s[i] == '\0')
			break ;
		if (s[i] && s[i] == SQUOTE)
		{
			str[total++] = s[i++];
			while (s[i] && s[i] != SQUOTE)
			{
				str[total++] = s[i++];
				if (s[i] == '\0')
					break ;
			}
			str[total++] = s[i++];
		}
		if (s[i] && s[i] == DQUOTE)
		{
			str[total++] = s[i++];
			while (s[i] && s[i] == '$')
				i += ft_checkdollar(&s[i], &total, str, env);
			if (s[i] == '\0')
				break ;
			while (s[i] && s[i] != DQUOTE)
			{
				while (s[i] && s[i] == '$')
					i += ft_checkdollar(&s[i], &total, str, env);
				if (s[i] == '\0')
					break ;
				str[total++] = s[i++];
			}
			str[total++] = s[i++];
		}
		if (s[i] == '\0')
			break ;
		str[total++] = s[i++];
	}
	return (str);
}

/*1
	input
"$SHLVL"	'$SHLVL'	"'$SHLVL'"	'"$SHLVL"'	'$SH"LVL'	"$SH'LVL"	"$"SHLVL	'$'SHLVL	$S'HLVL'	$S"HLVL"	$S'$SHLVL'	$S"$SHLVL"
	output
3			$SHLVL		'3'			"$SHLVL"	$SH"LVL		'LVL		$SHLVL		$SHLVL		HLVL		HLVL		$SHLVL		3
	my output
1			$SHLVL		'1'			"$SHLVL"	$SH"LVL		'LVL		$SHLVL		$SHLVL		HLVL		HLVL		$SHLVL			1 

$"PATH"
*/
