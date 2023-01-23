/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 04:01:39 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 07:11:09 by mgamil           ###   ########.fr       */
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
	ft_freetab(data->here->here_docs);
	// ft_freetab(data->here->filename);
	ft_freetab(data->split);
	ft_freetab(data->env);
	ft_freerr(node);
	// ft_free((void **)&cmd);

}

void	ft_errorcmd_bt(t_data *data, t_cmd *cmd, t_rr *node, char *str)
{
	ft_free((void **)&cmd->flags);
	ft_free((void **)&cmd->cmd);
	ft_freetab(data->split);
	ft_freerr(node);
	close(data->fd[0]);
	close(data->fd[1]);
}

int	error_fd_bt(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	if (errno == 13 && node->type != 4)
		ft_printf("bash: %s: Permission denied\n", node->content);
	else if (errno == 13 && node->type == 4)
		ft_printf("bash: %s: Permission denied\n", data->here->filename[index]);
	else if (node->type != 4)
		ft_printf("bash: %s: No such file or directory\n", node->content);
	else
		ft_printf("bash: %s: No such file or directory\n",
					data->here->filename[index]);
	ft_errorcmd_bt(data, cmd, cmd->redi, "");
	return (1);
}
