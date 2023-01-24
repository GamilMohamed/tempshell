/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 06:24:49 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 22:33:06 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_fd(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	if (errno == 13 && node->type != 4)
		fprintf(stderr, "bash: %s: Permission denied\n", node->content);
	else if (node->type != 4)
		fprintf(stderr, "bash: %s: No such file or directory\n", node->content);
	ft_errorcmd(data, cmd, cmd->redi, "");
	close(data->fd[1]);
	close(data->fd[0]);
	exit(1);
}

void	execve_error(t_data *data, char *str, char **tab, int boolean)
{
	if (boolean)
		fprintf(stderr, "%s: command not found\n", str);
	else if (errno == 13)
		fprintf(stderr, "bash: %s: Permission denied\n", str);
	else
		fprintf(stderr, "bash: %s: No such file or directory\n", str);
	data->status = 127;
	ft_freetab(tab);
}
