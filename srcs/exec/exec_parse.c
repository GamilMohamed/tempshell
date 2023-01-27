/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:20:33 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/26 16:28:49 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
void	initcommand(t_cmd *cmd, char *str, int count)
{
	(void)count;
	cmd->cmd = ft_strdup(str);
	cmd->flags = ft_realloc(cmd->flags, str);
}

static
void	flags_wild(t_cmd *cmd, char *tab)
{
	char	*wild;

	wild = 0;
	cmd->flags = ft_realloc(cmd->flags, " ");
	if (ft_strchr(tab, '*'))
	{
		wild = ft_wildcard(tab);
		cmd->flags = ft_realloc(cmd->flags, wild);
		ft_free((void **)&wild);
	}
	else
		cmd->flags = ft_realloc(cmd->flags, tab);
}

char	*checkstring(t_cmd *cmd, char *str)
{
	int		i;
	int		count;
	char	**tab;

	tab = ft_split(str, ' ');
	cmd->redi = 0;
	count = 0;
	i = -1;
	while (tab[++i])
	{
		if (!isaredirection(tab[i]) && !count)
			initcommand(cmd, tab[i], count++);
		else if (!isaredirection(tab[i]))
			flags_wild(cmd, tab[i]);
		else if (tab[i + 1])
		{
			i += ft_lstadd_back_rr(&cmd->redi, ft_lstnewrr(ft_strdup(tab[i
							+ 1]), isaredirection(tab[i])));
		}
	}
	ft_freetab(tab);
	return (NULL);
}
