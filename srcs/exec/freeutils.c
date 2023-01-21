/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 04:01:39 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/20 10:35:17 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freerr(t_rr *node)
{
	t_rr	*temp;

	while (node)
	{
		ft_free((void **)& node->content);
		temp = node->next;
		ft_free((void **)& node);
		node = temp;
	}
}

void	ft_errorcmd(t_data *data, t_cmd *cmd, t_rr *node, char *str)
{
	// ft_freepostexec(cmd, data);
	ft_free((void **)&cmd->flags);
	ft_free((void **)&cmd->cmd);
	ft_freetab(data->path);
	ft_freetab(data->here_docs);
	ft_freetab(data->filename);
	ft_freetab(data->split);
	ft_freetab(data->env);
	ft_freerr(node);
	// ft_free((void **)&cmd);

}