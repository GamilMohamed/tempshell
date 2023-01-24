/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:24:49 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 07:18:24 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fd(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	if (errno == 13 && node->type != 4)
		ft_printf("bash: %s: Permission denied\n", node->content);
	else if (node->type != 4)
		ft_printf("bash: %s: No such file or directory\n", node->content);
	ft_errorcmd(data, cmd, cmd->redi, "");
	close(data->fd[1]);
	close(data->fd[0]);
	exit(1);
}
