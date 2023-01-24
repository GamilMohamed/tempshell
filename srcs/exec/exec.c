/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 21:30:58 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minitrees.h"

void	execute(t_data *data, t_cmd *cmd, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;
	int		count;

	i = -1;
	data->status = 0;
	tab = ft_split(cmd->flags, ' ');
	while (tab[++i])
		tab[i] = invert(tab[i]);
	i = -1;
	cmd->cmd = invert(cmd->cmd);
	while (boolean && data->path && data->path[++i])
	{
		temp = ft_slash(data->path[i], cmd->cmd);
		if (access(temp, F_OK | X_OK) != -1)
			execve(temp, tab, data->env);
		free(temp);
	}
	if (!boolean)
		if (access(cmd->cmd, F_OK | X_OK) == 0)
			execve(cmd->cmd, tab, data->env);
	execve_error(data, cmd->cmd, tab, boolean);
}

int	exec_builtin(t_cmd *cmd, t_data *data)
{
	int	copyfd;

	if (!matching(cmd->cmd))
		return (0);
	copyfd = dup(STDOUT_FILENO);
	if (openfiles_bt(cmd->redi, data, cmd, 0))
	{
		dup2(copyfd, STDOUT_FILENO);
		close(copyfd);
		return (1);
	}
	ft_builtin(cmd, data);
	dup2(copyfd, STDOUT_FILENO);
	free_all(1, 0, &cmd->cmd, data->split);
	ft_freerr(cmd->redi);
	// close(data->fd[0]);
	close(data->fd[1]);
	close(copyfd);
	return (1);
}

int	exec_command(t_btree *tree, t_btree *head)
{
	int		i;
	char	**tab;
	t_cmd	cmd;
	char	*temp;
	int		status;

	temp = ft_expand(tree->node, tree->data->env);
	ft_bzero(&cmd, sizeof(t_cmd));
	tree->data->split = ft_split(temp, '|');
	tree->data->nbcmd = ft_countdelim(temp, '|');
	free(temp);
	i = -1;
	while (++i < tree->data->nbcmd)
		forker(tree, head, &cmd, i);
	free_all(1, 1, &cmd.flags, tree->data->split);
	close(tree->data->fd[0]);
	exec_waitpid(tree->data);
	signal(SIGINT, &ctrlc);
	return (0);
}

int	exec_tree(t_btree *tree, t_btree *head)
{
	tree->data->prev_pipes = -1;
	if (!ft_strcmp((char *)tree->node, "||"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, head);
		if (tree->data->status)
			return (exec_tree(tree->r, head));
		return (0);
	}
	else if (!ft_strcmp((char *)tree->node, "&&"))
	{
		tree->data->prev_pipes = -1;
		exec_tree(tree->l, head);
		if (!tree->data->status)
			return (exec_tree(tree->r, head));
		return (1);
	}
	return (exec_command(tree, head));
}
