/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@42.student.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:08:30 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/23 07:55:27 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	openfiles_bt(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	int		fd;
	t_rr	*head;

	head = node;
	while (node)
	{
		if (node->type == 1) // >
			fd = open(node->content, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 2) // >>
			fd = open(node->content, O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 3) // <
			fd = open(node->content, O_RDONLY);
		else if (node->type == 4) // <<
			fd = open(data->here->filename[data->here->hd++], O_RDONLY);
		if (fd == -1)
			if (error_fd_bt(node, data, cmd, index))
				return (1);
		if (node->type > 2)
			dupnclose(fd, STDIN_FILENO);
		else if (node->type < 3)
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
	}
	return (0);
}

void	openfiles(t_rr *node, t_data *data, t_cmd *cmd, int index)
{
	int		fd;
	t_rr	*head;

	head = node;
	while (node)
	{
		if (node->type == 1) // >
			fd = open(node->content, O_TRUNC | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 2) // >>
			fd = open(node->content, O_APPEND | O_WRONLY | O_CREAT, 0666);
		else if (node->type == 3) // <
			fd = open(node->content, O_RDONLY);
		else if (node->type == 4) // <<
			fd = open(data->here->filename[data->here->hd++], O_RDONLY);
		if (fd == -1)
			error_fd(node, data, cmd, index);
		if (node->type > 2)
			dupnclose(fd, STDIN_FILENO);
		else if (node->type < 3)
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
	}
}
