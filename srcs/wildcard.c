/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:59:25 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/20 10:48:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_str_wildcard_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '*')
		len++;
	if (str[len] == 0)
		len++;
	return (len);
}

char	*ft_strnstr_wcd(char *haystack, char *needle, int needle_len)
{
	int	h;
	int	n;

	h = -1;
	while (haystack[++h])
	{
		n = 0;
		while (needle[n] && needle[n] == haystack[h + n] && n < needle_len)
			n++;
		if (n < needle_len && !(needle[n]) && !haystack[h + n])
			n++;
		if (n == needle_len)
			return (haystack + h + n);
	}
	return (NULL);
}

char	*ft_strncmp_wcd(char *haystack, char *needle, int n)
{
	int	i;

	i = 0;
	while (i < n && haystack[i] && needle[i] && haystack[i] == needle[i])
		i++;
	if (i < n && !(haystack[i]) && !(needle[i]))
		i++;
	if (i == n)
		return (haystack + n);
	return (NULL);
}

int	check_wildcards(char *haystack, char *wildcards)
{
	int	w;
	int	w_trigger;

	while (*wildcards)
	{
		w = 0;
		w_trigger = (*wildcards == '*');
		while (*wildcards == '*')
			wildcards++;
		if (*wildcards)
		{
			ft_printf("*wildcards=%c\n", *wildcards);
			w = ft_str_wildcard_len(wildcards);
			if (w_trigger)
				haystack = ft_strnstr_wcd(haystack, wildcards, w);
			else
				haystack = ft_strncmp_wcd(haystack, wildcards, w);
			if (haystack == NULL)
				return (0);
			wildcards = wildcards + w - (wildcards[w - 1] == '\0');
		}
		if (w && !(*wildcards) && *haystack)
			return (0);
	}
	return (1);
}

char	*ft_wildcard(char *wildcards)
{
	char			*temp;
	DIR				*dir;
	struct dirent	*entry;
	char			*pwd;

	temp = 0;
	pwd = builtin_pwd(NULL);
	dir = opendir(pwd);
	free(pwd);
	entry = readdir(dir);
	while (entry)
	{
		// ft_printf("wildcards=%s\n", wildcards);
		while (wildcards[0] != '.' && entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			ft_printf("entry->d_name=%s\n", entry->d_name);
		}	
		ft_printf("jmechappe %s\n", entry->d_name);
		// if (!entry->d_name[0])
		// 	break ;
		if (check_wildcards(entry->d_name, wildcards))
		{
			temp = ft_realloc(temp, entry->d_name);
			temp = ft_realloc(temp, " ");
		}
		ft_printf("jme suis echappe:%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (temp);
}

// char	*ft_wildcard(char *str)
// {
// 	char *new;
// 	int i;

// 	i = -1;
// 	while (str[i])
// 	{
// 		while (ft_isspace(str[i]))
// 			i++;
// 	}
// 	return (new);
// }

/*
ls a*t | *
ls >a.out | a.out history.txt includes libft.a liblkriefft.a minishell srcs fichier ignore.txt libft liblkriefft Makefile objs

*/