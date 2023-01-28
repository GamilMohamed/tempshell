/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:25:57 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 02:05:07 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data, t_cmd *cmd, int boolean)
{
	char	*temp;
	char	**tab;
	int		i;
	int		count;

	i = -1;
	data->status = 0;
	tab = ft_split(cmd->flags, SPACES, & count);
	while (tab[++i])
		tab[i] = invert(tab[i]);
	i = -1;
	cmd->cmd = invert(cmd->cmd);
	cmd->cmd = ft_quote(cmd->cmd);
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
	if (!matching(cmd->cmd))
		return (0);
	data->copyfd = dup(STDOUT_FILENO);
	if (openfiles_bt(cmd->redi, data, cmd, 0))
	{
		dup2(data->copyfd, STDOUT_FILENO);
		close(data->copyfd);
		return (1);
	}
	data->status = ft_builtin(cmd, data);
	dup2(data->copyfd, STDOUT_FILENO);
	ft_freerr(cmd->redi);
	close(data->fd[1]);
	close(data->copyfd);
	return (1);
}


void	ft_invertspaces(char *str)
{
	int i = 0;
	int quote = 0;

	while (str[i])
	{
		while (str[i] && (str[i] == SQUOTE || str[i] == DQUOTE))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (ft_strchr("\t\v\n >|&)(<", str[i]))
					str[i] = -str[i];
				if (!str[i++])
					break ;
			}
			if (!str[i++])
				break ;
		}
		if (!str[i++])
			break ;
	}
}

int	exec_command(t_btree *tree, t_btree *head)
{
	int		i;
	char	**tab;
	t_cmd	cmd;
	char	*temp;
	int		status;

	ft_bzero(&cmd, sizeof(t_cmd));
	ft_printf("START temp=%s\n", tree->node);
	temp = ft_expand(tree->data, tree->node);
	ft_printf("EXPAND temp=%s\n", temp);
	ft_printf("INVERT SPACES temp=%s\n", temp);
	ft_invertspaces(temp);
	ft_printf("QUOTE temp=%s\n", temp);
	temp = ft_quote(temp);
	tree->data->split = ft_split(temp, "|", & tree->data->nbcmd);
	free(temp);
	i = -1;
	while (++i < tree->data->nbcmd)
		forker(tree, head, &cmd, i);
	free_all(2, 1, &cmd.cmd, &cmd.flags, tree->data->split);
	if (tree->data->nbcmd)
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
