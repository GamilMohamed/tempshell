/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:19:02 by mgamil            #+#    #+#             */
/*   Updated: 2023/01/24 22:35:10 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printstruct(t_cmd *cmd, void *str, t_data *data, int index)
{
	fprintf(stderr, "\t node : [%s] (%i cmds)\n", (char *)str, data->nbcmd);
	fprintf(stderr, "\t\t struct of part : [%s]\n", data->split[index]);
	fprintf(stderr, "COMMAND NAME={%s}\n", cmd->cmd);
	fprintf(stderr, "COMMAND FLAGS={%s}\n", cmd->flags);
	fprintf(stderr, "COMMAND REDI\n");
	ft_printlist(cmd->redi);
}

void	ft_child(t_btree *tree, t_btree *head, t_cmd *cmd, int index)
{
	int	status;

	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, &antislash);
	// ft_printf("test\n");
	forking(tree->data, index, tree->data->nbcmd, cmd);
	ft_errorcmd(tree->data, cmd, cmd->redi, "");
	freestruct(tree->data);
	status = tree->data->status;
	exit(status);
}

void	ft_father(t_btree *tree, t_btree *head, t_cmd *cmd)
{
	// ft_printf("%i|%i|%i\n", tree->data->fd[0], tree->data->fd[1], tree->data->prev_pipes);	
	close(tree->data->fd[1]);
	if (tree->data->prev_pipes != -1)
		close(tree->data->prev_pipes);
	tree->data->prev_pipes = tree->data->fd[0];
	free_all(2, 0, &cmd->cmd, &cmd->flags);
	ft_freerr(cmd->redi);
	signal(SIGQUIT, SIG_IGN);
}

void	forker(t_btree *tree, t_btree *head, t_cmd *cmd, int i)
{
	tree->data->split[i] = ft_spacestr(tree->data->split[i]);
	checkstring(cmd, tree->data->split[i]);
	printstruct(cmd, tree->node, tree->data, i);
	pipe(tree->data->fd);
	if (tree->data->nbcmd == 1 && exec_builtin(cmd, tree->data))
		return ;
	signal(SIGINT, SIG_IGN);
	tree->data->pid[i] = fork();
	if (tree->data->pid[i] == 0)
		ft_child(tree, head, cmd, i);
	else if (tree->data->pid[i] > 0)
		ft_father(tree, head, cmd);
}

void	forking(t_data *data, int index, int max, t_cmd *cmd)
{
	if (index != max - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0)
		dupnclose(data->prev_pipes, STDIN_FILENO);
	openfiles(cmd->redi, data, cmd, index);
	close(data->fd[1]);
	close(data->fd[0]);
	if (matching(cmd->cmd))
		ft_builtin(cmd, data);
	else if (cmd->cmd)
		execute(data, cmd, !(ft_strchr(cmd->cmd, '/')));
}
