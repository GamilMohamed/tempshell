/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:08:30 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 07:56:48 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
int	get_pipe(t_here *here, t_data *data, char *str)
{
	int i = -1;

	while (++i < data->nb_here)
	{
		if (!ft_strcmp(data->here[i].delim, str))
			return(here[i].pipe[0]);
	}
	return (-1);
}

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
			fd = get_pipe(data->here, data, node->content);
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
			fd = get_pipe(data->here, data, node->content);
		if (fd == -1)
			error_fd(node, data, cmd, index);
		if (node->type > 2)
			dupnclose(fd, STDIN_FILENO);
		else if (node->type < 3)
			dupnclose(fd, STDOUT_FILENO);
		node = node->next;
	}
}
