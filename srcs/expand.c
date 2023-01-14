/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 01:50:36 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/14 09:19:34 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkdollar(char *s, int *total, char *string)
{
	int		i;
	char	*str;
	char	*new;
	int		j;

	i = 1;
	while (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
		i++;
	str = ft_substr(s, 1, i - 1);
	// ft_strlcpy(str, &s[1], i);
	new = getenv(str);
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
			i += ft_checkdollar(&s[i], &total, NULL);
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
				i += ft_checkdollar(&s[i], &total, NULL);
			if (s[i] == '\0')
				break ;
			while (s[i] && s[i] != DQUOTE)
			{
				while (s[i] && s[i] == '$')
					i += ft_checkdollar(&s[i], &total, NULL);
				if (s[i] == '\0')
					break ;
				total++;
				i++;
			}
			total++;
			i++;
		}
		total++;
		i++;
	}
	// ft_printf("[i]=%i\n", i);
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
			i += ft_checkdollar(&s[i], &total, str);
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
				i += ft_checkdollar(&s[i], &total, str);
			if (s[i] == '\0')
				break ;
			while (s[i] && s[i] != DQUOTE)
			{
				while (s[i] && s[i] == '$')
					i += ft_checkdollar(&s[i], &total, str);
				if (s[i] == '\0')
					break ;
				str[total++] = s[i++];
			}
			str[total++] = s[i++];
		}
		str[total++] = s[i++];
	}
	free(s);
	// printf("str=%s\n", str);
	// ft_printf("lenstr=%i\n", ft_strlen(str));
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
