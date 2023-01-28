/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 10:21:21 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/28 01:49:10 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_slash(char *path, char *cmd)
{
	char	*var;
	size_t	i;
	size_t	x;

	var = ft_calloc(ft_strlen(path) + ft_strlen(cmd) + 2, 1);
	if (!var)
		return (NULL);
	i = -1;
	while (path[++i])
		var[i] = path[i];
	var[i++] = '/';
	x = -1;
	while (cmd[++x])
		var[i + x] = cmd[x];
	var[i + x] = '\0';
	return (var);
}

int	ft_lstadd_back_rr(t_rr **lst, t_rr *var)
{
	t_rr	*begin;

	begin = *lst;
	if (!*lst)
		*lst = var;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = var;
	}
	return (1);
}

t_rr	*ft_lstnewrr(char *content, int type)
{
	t_rr	*elem;

	elem = ft_calloc(sizeof(*elem), 1);
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

void	ft_printlist(t_rr *temp)
{
	t_rr	*head;

	head = temp;
	while (head)
	{
		fprintf(stderr, "[%i]", head->type);
		fprintf(stderr, "%s\n", head->content);
		head = head->next;
	}
}

char	*invert(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 0)
			str[i] = -str[i];
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == 6)
			str[i] = '\0';
	}
	return (str);
}
